
#include <tacopie/tacopie>
#include <iostream>
#include <colorizer/colorizer.hpp>
#include <csignal>
#include <functional>
#include <sstream>
#include <string>
#include "server.hpp"

#include <string.h>

tacopie::tcp_server s;

void messageReceived(const std::shared_ptr<tacopie::tcp_client>& client, const tacopie::tcp_client::read_result& res)
{
    if(res.success)
    {
        /*
         * A quick note about read_result's structure:
         * success - bool, denotes the read operation's success value (duh)
         * buffer - std::vector<char>, the bytes from the read operation
         */
        std::vector<char> result_vec = res.buffer;
        int len = result_vec.size();
        char buf[len + 1];
        memcpy(buf, result_vec.data(), len);
        buf[len] = 0;
        std::cout << "A client sent the follwing message: ";
        std::cout << buf;
        std::cout << std::endl;
        
        std::string msg = buf;
        
        //client->async_write({std::vector<char>{msg.begin(), msg.end()}, nullptr});
        //std::cout << "Sent to client:\n" << msg << std::endl;
        //client->async_read({1024, std::bind(&messageReceived, client, std::placeholders::_1)});
        
        std::list<std::shared_ptr<tacopie::tcp_client>> clientList;
        clientList = s.get_clients();
        int count = 0;
        for (std::list<std::shared_ptr<tacopie::tcp_client>>::const_iterator it = clientList.begin(); it != clientList.end(); it++) {
            (*it)->async_write({std::vector<char>{msg.begin(), msg.end()}, nullptr});
            std::cout << "Sent to client" << count++ << ":\n" << msg << std::endl;
            (*it)->async_read({1024, std::bind(&messageReceived, (*it), std::placeholders::_1)});
        }
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
