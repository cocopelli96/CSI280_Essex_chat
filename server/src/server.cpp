
#include <tacopie/tacopie>
#include <iostream>
#include <colorizer/colorizer.hpp>
#include <csignal>
#include <functional>
#include <sstream>
#include "server.hpp"
#include "server_environment.hpp"

tacopie::tcp_server s;

int main(int argc, char* argv[])
{
  // Initializing some of the base colours to be used in prompts...
  std::string error = construct_color(ConsoleColor::RED, ConsoleColor::BLACK, true);
  std::string info = construct_color(ConsoleColor::GREEN, ConsoleColor::BLACK, true);
  std::string reset = reset_color();
  
  std::cout << info << "Essex " << SERVER_VERSION << " is starting up..." << reset << std::endl;

  s.start("127.0.0.1", 7331, [] (const std::shared_ptr<tacopie::tcp_client>& client) -> bool {
      std::cout << "Client has connected to server..." << std::endl;
      ServerEnvironment *environment = ((ServerEnvironment*)(ServerEnvironment::getEnvironment));
      client->async_read({1024, std::bind(ServerEnvironment::recieveFromClient, environment, client, std::placeholders::_1)});
      return true;
    });

  ServerEnvironment::createServerEnvironment(&s);

  std::signal(SIGINT, [](int signal) {
      s.stop();
      std::cout << "Bye!" << std::endl;
    });
  
  while(s.is_running())
  {
    
  }

  return 0;
}
