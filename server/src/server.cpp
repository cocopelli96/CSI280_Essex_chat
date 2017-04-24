
#include <tacopie/tacopie>
#include <iostream>
#include <colorizer/colorizer.hpp>
#include <csignal>
#include <functional>
#include <sstream>
#include <string>
#include "server.hpp"

tacopie::tcp_server s;

void messageReceived(const std::shared_ptr<tacopie::tcp_client>& client, const tacopie::tcp_client::read_result& res)
{
    if(res.success)
    {
        std::cout << "Our client sent something!" << std::endl;
        /*
         * A quick note about read_result's structure:
         * success - bool, denotes the read operation's success value (duh)
         * buffer - std::vector<char>, the bytes from the read operation
         */
        std::cout << "A client sent the follwing message: ";
        for(auto i = res.buffer.begin(); i != res.buffer.end(); i++)
        {
            std::cout << *i;
        }
        std::cout << std::endl;
        
        std::string msg;
        msg = "Message recieved. The packet had ";
        msg += std::to_string(res.buffer.size());
        msg += " bytes in it.\n";
        
        client->async_write({std::vector<char>{msg.begin(), msg.end()}, nullptr});
        client->async_read({1024, std::bind(&messageReceived, client, std::placeholders::_1)});
        std::cout << "Sent to client:\n" << msg;
    }
}


int main(int argc, char* argv[])
{
    // Initializing some of the base colours to be used in prompts...
    std::string error = construct_color(ConsoleColor::RED, ConsoleColor::BLACK, true);
    std::string info = construct_color(ConsoleColor::GREEN, ConsoleColor::BLACK, true);
    std::string reset = reset_color();
  
    std::cout << info << "Essex " << SERVER_VERSION << " is starting up..." << reset << std::endl;

    s.start("0.0.0.0", 7331, [] (const std::shared_ptr<tacopie::tcp_client>& client) -> bool {
        std::cout << "Client has connected to server..." << std::endl;
        client->async_read({1024, std::bind(&messageReceived, client, std::placeholders::_1)});
        return true;
    });

    std::signal(SIGINT, [](int signal)
    {
        s.stop();
        std::cout << "Bye!" << std::endl;
    });
  
    while(s.is_running())
    {

    }

    return 0;
}
