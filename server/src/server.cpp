
#include <tacopie/tacopie>
#include <iostream>
#include <colorizer/colorizer.hpp>

#include "server.hpp"

int main(int argc, char* argv[])
{
  std::string error = construct_color(ConsoleColor::RED, ConsoleColor::BLACK, true);
  std::string info = construct_color(ConsoleColor::GREEN, ConsoleColor::BLACK, true);
  std::string reset = reset_color();
  std::cout << info << "Essex " << SERVER_VERSION << " is starting up..." << reset << std::endl;
}
