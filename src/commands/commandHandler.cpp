#include "../../inc/IRC.hpp"
#include <string>

void IRC::JoinChannel(Client &client, string channelName, string channelPwd)
{
    bool join = false;
    list<Channel>::iterator channel = this->channels.begin();
    while (channel != this->channels.end())
    {
        if (channel->getName() == channelName)
        {
            join = true;
            break;
        }
        channel++;
    }
    if (join)
    {
        cout << client.getNickname() << " joining channel" << endl;
        if (channel->getPass() == channelPwd)
        {
            channel->addClient(client);
            sendMsg(client.getSockfd(), client.getIDENTITY() + " JOIN " + channelName);
        }
        else
            sendMsg(client.getSockfd(), "475 : Failed to join the " + channelName + " bad password.");
    }
    else
    {
        cout << client.getNickname() << " creating channel" << endl;
        Channel create(channelName,channelPwd);
        create.setName(channelName);
        create.setModfd(client.getSockfd());
        create.addClient(client);
        this->channels.push_back(create);
        //sendMsg(client.getSockfd(), client.getNickname() + " " + channelName + " 331 : No topic is set");
        sendMsg(client.getSockfd(), client.getIDENTITY() + " JOIN " + channelName);
    }
}

void IRC::privmsg(string target, string _msg)
{
    cout << "target = " << target << " _msg = " << _msg << endl;
    string msg = _msg.substr(1);
    if (target[0] == '#')
    {
        cout << "-----------Detected it a channel !" << endl;
        string channelName = target;
        list<Channel>::iterator itChannel = this->channels.begin();
        list<Client>::iterator itClients;
        while (itChannel != this->channels.end())
        {
            cout << "-----------Searching for channel, is it the channel ( " << channelName << " == "<< itChannel->getName() << " )" << endl;
            if (channelName == itChannel->getName())
            {
                cout << "-----------Channel Found ! " << itChannel->getName() <<" Looking for the clients in the channel" << endl;
                itClients = itChannel->getClients().begin();
                cout << "-----------Clients counts are " << itChannel->getClients().size() << endl;
                while (itClients != itChannel->getClients().end())
                {
                    cout <<"Found a client to send msg client is" <<"[" << itClients->getSockfd() << "]" << itClients->getNickname() << endl;
                    sendMsg(itClients->getSockfd(), msg);
                    itClients++;
                }
            }
            itChannel++;
        }
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
                    string target;
                    iss >> target;
                    privmsg(target, iss.str());
                    break;
                }
                else if (token == "JOIN")
                {
                    string channel, pwd;
                    iss >> channel >> pwd;
                    if (channel[0] == '#')
                        JoinChannel(client, channel, pwd);
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
