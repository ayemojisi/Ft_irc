#include "../../inc/IRC.hpp"

void IRC::CommandHandler(Client &client, string cmd)
{
    std::istringstream iss(cmd);
    string token, result;
    while (iss >> token)
    {
        if (token == "PASS")
        {
            if (client.getPassword() != this->password)
                sendMsg(client.getSockfd(), ":server 464 * :Password is incorrect");
            iss >> result;
            client.setPassword(result);
        }
        if (client.getPassword() == this->password)
        {
            if (token == "NICK")
            {
                iss >> result;
                client.setNickname(result);
            }
            else if (token == "USER")
            {
                iss >> result;
                client.setUsername(result);
            }
        }
        // else if(token == "PING")
        else if (!client.getIsAuthed())
        {
            if ((token != "PRIVMSG" && token != "JOIN" && token != "TOPIC" &&
                 token != "KICK" && token != "INVITE" && token != "LIST" &&
                 token != "MODE" && token != "PART" && token != "QUIT"))
                sendMsg(client.getSockfd(), ": Command is not found.\r\n");
            else
                sendMsg(client.getSockfd(), FG_LIGHTRED + client.getNickname() +
                                                " Please login!\r\n" + RESET);
        }
        if (!client.getPassword().empty() && client.getPassword() == this->password && !client.getUsername().empty() && !client.getNickname().empty() && !client.getIsAuthed())
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
        }
    }
}