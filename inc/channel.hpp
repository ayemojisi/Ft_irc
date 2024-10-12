#pragma once

#include "client.hpp"
#include "libs.hpp"
#include <list>

class Channel {
private:
  string name;
  string topic;
  string pass;
  map<int, Client> clients;
  list<int> modfd;

public:
  Channel();
  Channel(string name);
  ~Channel();

  int joinChannel(string name, string pass);
  int addModfd(int sockfd);
  int addClient(Client client);
  int removeClient(int sockfd);
  int setModfd(int sockfd);
  int searchClient(string nick);

  // Get-Set
  string getName() { return this->name; }
  string getTopic() { return this->topic; }
  map<int, Client> getClients() { return this->clients; }
  //---------------------
  void setName(string name) { this->name = name; }
  void setPass(string pass) { this->pass = pass; }
  void setTopic(string topic) { this->topic = topic; }
};
