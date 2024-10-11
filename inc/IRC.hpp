#pragma once

#include "channel.hpp"
#include "client.hpp"

#define BACKLOG 10       // how many pending connections queue will hold
#define MAXCLIENTS 10    // maximum number of clients
#define BUFFER_SIZE 4096 // buffer size

class IRC {
private:
  int port;
  int sockfd;
  int maxfd;
  int newClientfd;
  int itsMine;
  int maxClients;
  fd_set masterfd;
  fd_set readfd;
  string password;
  sockaddr_in serverAddr;
  sockaddr_in clientAddr;
  map<int, Client> clients;
  list<Channel> channels;

  IRC();

public:
  // methods
  void start();
  void newClientAdd();
  void handleClient(int sockfd);
  void HandleClientQuit();

  // constructors
  IRC(int port, string password);
  IRC(const IRC &irc);
  ~IRC() { close(sockfd); }
};

string fullMsg(std::istringstream iss);
void sendMsg(int targetFd, string msg);
void sendAllClientMsg(map<int, Client> &clientList, string msg);
