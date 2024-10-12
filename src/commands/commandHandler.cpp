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
            }
            if (client.getIsAuthed())
            {
                /* Bunlar eklenecek
    if(client.getIsAuth() && token == "PRIVMSG")
                      else if(client.getIsAuth() && token == "JOIN")
                      else if(client.getIsAuth() && token == "TOPIC")
                      else if(client.getIsAuth() && token == "KICK")
                      else if(client.getIsAuth() && token == "LIST")
                      else if(client.getIsAuth() && token == "INVITE")
                      else if(client.getIsAuth() && token == "MODE")
                      else if(client.getIsAuth() && token == "PART")
                      else if(client.getIsAuth() && token == "QUIT")
                      else if(client.getIsAuth() && token == 	"NOTICE")
                      else if(client.getIsAuth()){
    */
                if ((token != "PRIVMSG" && token != "JOIN" && token != "TOPIC" &&
                     token != "KICK" && token != "INVITE" && token != "LIST" &&
                     token != "MODE" && token != "PART" && token != "QUIT"))
                    sendMsg(client.getSockfd(), ": Command is not found.");
                else
                    sendMsg(client.getSockfd(), FG_LIGHTRED + client.getNickname() +
                                                    " Please login!" + RESET);
            }
        }
    }
}