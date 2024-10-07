#pragma once

#include "client.hpp"
#include "libs.hpp"

class Channel {
private:
  string name;
  list<Client> clients;

public:
  Channel(){};
  Channel(string name) { this->name = name; }
  ~Channel(){};
};
