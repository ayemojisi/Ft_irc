#include "../inc/client.hpp"

Client::Client(int sockfd, sockaddr_in clientAddr) {
  this->sockfd = sockfd;
  this->clientAddr = clientAddr;
  cout << "Client connected" << endl;
  cout << "IP: " << inet_ntoa(clientAddr.sin_addr) << endl;
  cout << "Port: " << ntohs(clientAddr.sin_port) << endl;
  cout << "Socket: " << sockfd << endl;
  cout << "-------------------" << endl;
}

Client::Client(const Client &client) {
  if (this != &client) {
    this->sockfd = client.sockfd;
    this->clientAddr = client.clientAddr;
  }
}

Client &Client::operator=(const Client &client) {
  if (this != &client) {
    this->sockfd = client.sockfd;
    this->clientAddr = client.clientAddr;
  }
  return *this;
}

Client::~Client() {}
