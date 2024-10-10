#pragma once

#include "libs.hpp"

class Channel {
private:
  string name;
  string type;
  string topic;

public:
  Channel(){};
  Channel(string name) { this->name = name; }
  ~Channel(){};
};
