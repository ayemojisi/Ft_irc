#pragma once

#include "style.hpp"
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <list>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;

class IRC {
private:
  int port;
  int sock;
  int opt;
  string password;
  string buffer;
  sockaddr_in serverAddr;

public:
    //methods
    void start();
    void send(string message);

    //constructors
  IRC(){};
  IRC(int port, string password){
      setPort(port);
      setPassword(password);

    if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      throw std::runtime_error("Socket creation error");
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR , &this->opt, sizeof(int)) == -1)
      throw std::runtime_error("Socket option error");
    cout << FG_GREEN << "Socket created..." << RESET << endl;
    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_addr.s_addr = INADDR_ANY;
    this->serverAddr.sin_port = htons(getPort());
    memset(&(this->serverAddr.sin_zero), '\0', 8);
    if (bind(getSock(), (struct sockaddr *)&this->serverAddr, sizeof(getServerAddr())))
        throw std::runtime_error("Bind error");
    cout << FG_GREEN << "Binded to port " << getPort() << RESET << endl;
    if (listen(getSock(), 10) < 0)
        throw std::runtime_error("Listen error");
    cout << FG_GREEN << "Listening on port " << getPort() << RESET << endl;
  };
  IRC(const IRC &irc)
  {
    if (this != &irc) {
      this->port = irc.port;
      this->password = irc.password;
    }
  };
  ~IRC() { close(sock); }

  //set-get
  void setPort(int& port) { this->port = port; }
  void setSock(int& sock) { this->sock = sock; }
  void setPassword(string& password) { this->password = password; }
  void setBuffer(string& buffer) { this->buffer = buffer; }
  void setServerAddr(sockaddr_in& serverAddr) { this->serverAddr = serverAddr; }
  //--------------------------------//
  int getPort() { return this->port; }
  int getSock() { return this->sock; }
  string getPassword() { return this->password; }
  string getBuffer() { return this->buffer; }
  sockaddr_in getServerAddr() { return this->serverAddr; }
};
