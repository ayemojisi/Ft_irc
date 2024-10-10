#pragma once

#include "client.hpp"
#include "libs.hpp"

string fullMsg(std::istringstream iss);
void sendMsg(int targetFd, string msg);
void sendAllClientMsg(map<int, Client> &clientList, string msg);
