#include "../../inc/IRC.hpp"

void IRC::JoinChannel(Client &client, string channelName, string channelPwd)
{
    bool join = false;
    std::list<Channel>::iterator it = this->channels.begin();
    while (it != this->channels.end())
    {
        if (it->getName() == channelName)
        {
            join = true;
            break;
        }
        it++;
    }
    if (join)
    {
        cout << client.getNickname() << " joining channel" << endl;
        if (it->getPass() == channelPwd)
            it->addClient(client);
        else
            sendMsg(client.getSockfd(), "475 : Failed to join the #" + channelName + " bad password.");
    }
    else
    {
        cout << client.getNickname() << " creating channel" << endl;
        Channel create(channelName,channelPwd);
        create.setModfd(client.getSockfd());
        create.addClient(client);
        this->channels.push_back(create);
        sendMsg(client.getSockfd(), "332 :");
    }
}

void IRC::CommandHandler(Client &client, string cmd)
{
    std::istringstream iss(cmd);
    string token, result;
    while (iss >> token)
    {
        if (client.getPassword() != this->password)
        {
            if (token == "PASS")
            {
                iss >> result;
                if (result[0] == ':')
                    result.erase(0, 1);
                client.setPassword(result);
                if (client.getPassword() != this->password)
                    sendMsg(client.getSockfd(), ERR_PASSWMISMATCH);
                else
                    sendMsg(client.getSockfd(), ":GRANTED : Password is correct enter your USER/NICK");
            }
            else
                sendMsg(client.getSockfd(), ERR_UNKNOWNCOMMAND);
        }
        else
        {
            if (token == "NICK")
            {
                iss >> result;
                if (!result.empty())
                    client.setNickname(result);
                else
                    sendMsg(client.getSockfd(), ": NICK can't be empty");
            }
            else if (token == "USER")
            {
                iss >> result;
                if (!result.empty())
                    client.setUsername(result);
                else
                    sendMsg(client.getSockfd(), ": USER can't be empty");
            }
            if (!client.getUsername().empty() && !client.getNickname().empty() && !client.getIsAuthed())
            {
                sendMsg(client.getSockfd(), RPL_WELCOME(client.getUsername()));
                client.setIsAuthed(true);
                break;
            }
            if (client.getIsAuthed())
            {
                if (token == "PRIVMSG")
                {
                    break;
                }
                else if (token == "JOIN")
                {
                    string channel, pwd;
                    iss >> channel >> pwd;
                    if (channel[0] == '#')
                        JoinChannel(client,channel, pwd);
                    else
                        sendMsg(client.getSockfd(), "Error: Channel name should be start with #");
                    break;
                }
                else if (token == "TOPIC")
                {
                    break;
                }
                else if (token == "KICK")
                {
                    break;
                }
                else if (token == "LIST")
                {
                    break;
                }
                else if (token == "INVITE")
                {
                    break;
                }
                else if (token == "MODE")//mod verir
                {
                    break;
                }
                else if (token == "PART")//kanaldan ayrılıyor
                {
                    break;
                }
                else if (token == "QUIT")//serverden ayrılıyor
                {
                    break;
                }
                else if (token == "NOTICE")
                {
                    break;
                }
                else if (token == "PING")
                {
                    sendMsg(client.getSockfd(), cmd);
                    break;
                }
                else if (token == "PONG")
                {
                    sendMsg(client.getSockfd(), token);
                    break;
                }
                else
                {
                    sendMsg(client.getSockfd(), token + " Command is not found.");
                    break;
                }
            }
        }
    }
}
