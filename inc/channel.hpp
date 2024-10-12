#pragma once

#include "libs.hpp"
#include "client.hpp"

class Channel {
private:
  string name;
  string topic;
  string password;
  map<int, Client> clients;
  Client admin;

public:
  Channel(){};
  Channel(string name) { this->name = name; }
  ~Channel(){};
};
