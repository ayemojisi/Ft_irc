#include "../../inc/IRC.hpp"

string fullMsg(std::istringstream iss) {
  string result = "";
  string msg;
  while (iss >> msg) {
    if (result.empty())
      result = msg;
    else
      result += " " + msg;
  }
  return result;
}

void sendMsg(int targetFd, string msg) {
  if (send(targetFd, msg.c_str(), msg.length(), 0) == -1)
    std::runtime_error("Send error");
}

void sendAllClientMsg(map<int, Client> &clientList, string msg) {
  std::map<int, Client>::iterator us = clientList.begin();
  while (us != clientList.end()) {
    send(us->second.getSockfd(), msg.c_str(), msg.length(), 0);
    us++;
  }
}
