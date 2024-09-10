#include "../inc/IRC.hpp"

static bool checkPort(const char *port) {
  int p;
  try {
    p = atoi(port);
  } catch (std::exception &e) {
    std::cout << FG_RED << "Invalid port number: " << RESET << port
              << std::endl;
    return true;
  }
  if (p < 1024 || p > 65535) {
    std::cout << FG_RED << "Invalid port number: " << RESET << port
              << std::endl;
    return true;
  }
  return false;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << FG_GREEN << "Usage: " << RESET << argv[0]
              << " <Port> <Password>" << std::endl;
    return 1;
  }
  if (checkPort(argv[1]))
    return 1;
  try {
    IRC irc(atoi(argv[1]), argv[2]);
    irc.start();
  } catch (std::exception &e) {
    std::cerr << FG_RED << "Error: " << RESET << e.what() << std::endl;
  }
  return 0;
}
