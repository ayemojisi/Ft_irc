#include "../inc/channel.hpp"

Channel::Channel() {
  cout << FG_YELLOW << "   Channel Info\n"
       << "――――――――――――――――――――――׀\n"
       << " Name  ׀ " << this->getName() << "\n"
       << " Topic ׀ " << this->getTopic() << endl;
}

Channel::Channel(string name) { this->name = name; }

Channel::~Channel() {}

int joinChannel(string name, string pass) { return 0; }
