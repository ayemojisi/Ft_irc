#include "../../inc/IRC.hpp"

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
                else if (token == "MODE")
                {
                    break;
                }
                else if (token == "PART")
                {
                    break;
                }
                else if (token == "QUIT")
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