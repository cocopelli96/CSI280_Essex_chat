
#include <tacopie/tacopie>
#include <iostream>
#include <colorizer/colorizer.hpp>

#include "server.hpp"

int main(int argc, char* argv[])
{
  std::cout << construct_color(ConsoleColor::YELLOW, ConsoleColor::RED, true) << "Essex " << SERVER_VERSION << " is starting up...\x1b[0m" << std::endl;
}
