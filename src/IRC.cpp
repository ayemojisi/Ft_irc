#include "../inc/IRC.hpp"
#include "../inc/client.hpp"
#include <arpa/inet.h>
#include <cstdio>
#include <sstream>
#include <string>
#include <sys/select.h>

IRC::IRC(int port, string password) {
  this->port = port;
  this->password = password;
  this->maxClients = MAXCLIENTS;
  itsMine = 1;

  if ((this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    throw runtime_error("Socket creation error");
  if (setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &this->itsMine,
                 sizeof(int)) < 0)
    throw runtime_error("Socket option [setsockopt] error");
  if (fcntl(this->sockfd, F_SETFL, O_NONBLOCK) == -1)
    throw runtime_error("Socket option [fcntl] error");
  cout << FG_GREEN << "Socket created..." << RESET << endl;

  this->serverAddr.sin_family = AF_INET;
  this->serverAddr.sin_addr.s_addr = INADDR_ANY;
  this->serverAddr.sin_port = htons(this->port);
  memset(&(this->serverAddr.sin_zero), '\0', 8);
  if (bind(this->sockfd, (struct sockaddr *)&this->serverAddr,
           sizeof(this->serverAddr)) < 0)
    throw runtime_error("Bind error");
  cout << FG_GREEN << "Binded to port " << this->port << RESET << endl;
  if (listen(this->sockfd, BACKLOG) < 0)
    throw runtime_error("Listen error");
  FD_SET(this->sockfd, &this->masterfd);
  this->maxfd = this->sockfd;
  cout << FG_GREEN << "Listening on port " << this->port << RESET << "\n"
       << endl;
};

IRC::IRC(const IRC &irc) {
  if (this != &irc) {
    this->port = irc.port;
    this->password = irc.password;
  }
};

void IRC::start() {
  while (true) {
    this->readfd = this->masterfd;
    int selectStatus = select(this->maxfd + 1, &this->readfd, NULL, NULL, NULL);
    switch (selectStatus) {
    case (0): {
      cout << FG_YELLOW << "Select Timeout..." << RESET << endl;
      break;
    }
    case (-1):
      throw runtime_error("Select error");
    default: {
      for (int i = 0; i <= this->maxfd; i++) {
        if (FD_ISSET(i, &this->readfd)) {
          if (i == this->sockfd)
            newClientAdd();
          else
            handleClient(i);
        }
      }
      break;
    }
    }
  }
}

void IRC::newClientAdd() {
  int clientLen = sizeof(this->clientAddr);
  if ((this->newClientfd =
           accept(this->sockfd, (struct sockaddr *)&this->clientAddr,
                  (socklen_t *)&clientLen)) == -1)
    throw runtime_error("Accept error");
  else {
    FD_SET(this->newClientfd, &this->masterfd);
    if (this->newClientfd > this->maxfd)
      this->maxfd = this->newClientfd;
    Client newClient(this->newClientfd, this->clientAddr);
    this->clients.insert(pair<int, Client>(this->newClientfd, newClient));
  }
}

static void handleClientQuit(int sockfd, fd_set &masterfd,
                             map<int, Client> &clients) {
  Client &client = clients.find(sockfd)->second;
  cout << FG_RED << "[" << sockfd << "] "
       << (client.getNickname().empty() ? "client" : client.getNickname())
       << " is Disconnected" << endl
       << RESET;
  close(sockfd);
  FD_CLR(sockfd, &masterfd);
  clients.erase(sockfd);
}

void IRC::handleClient(int sockfd) {
  Client &client = this->clients.find(sockfd)->second;
  char buff[BUFFER_SIZE] = {0};
  int nbytes;
  if ((nbytes = recv(client.getSockfd(), buff, sizeof(buff) - 1, 0)) <= 0) {
    if (nbytes != 0)
      cout << FG_RED + client.getUsername() + " its Quit" + RESET;
    handleClientQuit(sockfd, this->masterfd, this->clients);
  } else {
    std::istringstream iss(buff);
    string token, result;
    buff[nbytes] = '\0';
    while (iss >> token) {
      if (token == "NICK") {
        iss >> result;
        client.setNickname(result);
      } else if (token == "PASS") {
        iss >> result;
        client.setPassword(result);
      } else if (token == "USER") {
        iss >> result;
        client.setUsername(result);
      }
      // else if(token == "PING")
      else if (!client.getIsAuthed()) {
        if ((token != "PRIVMSG" && token != "JOIN" && token != "TOPIC" &&
             token != "KICK" && token != "INVITE" && token != "LIST" &&
             token != "MODE" && token != "PART" && token != "QUIT"))
          sendMsg(client.getSockfd(),
                  client.getNickname() + "Command is not found.\r\n");
        else
          sendMsg(client.getSockfd(), FG_LIGHTRED + client.getNickname() +
                                          " Please login!\r\n" + RESET);
        while (iss >> token)
          ;
      }
      if (!client.getPassword().empty() && !client.getUsername().empty() &&
          !client.getNickname().empty() && !client.getIsAuthed()) {
        sendMsg(client.getSockfd(),
                ": 001 " + client.getUsername() + ". Hello Everybody.");
        client.setIsAuthed(true);
        continue;
      }

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
    cout << FG_CYAN << "[" << sockfd << "] "
         << (client.getNickname().empty() ? "client" : client.getNickname())
         << " : " << FG_WHITE << buff << endl
         << RESET;
    sendAllClientMsg(this->clients, buff);
  }
}
