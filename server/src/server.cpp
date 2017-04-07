
#include <tacopie/tacopie>
#include <iostream>
#include <colorizer/colorizer.hpp>
#include <csignal>
#include <functional>
#include <sstream>
#include "server.hpp"

tacopie::tcp_server s;

void messageReceived(const std::shared_ptr<tacopie::tcp_client>& client, const tacopie::tcp_client::read_result& res)
{
    if(res.success)
    {
        std::cout << "Our client sent something!" << std::endl;
        client->async_read({1024, std::bind(&messageReceived, client, std::placeholders::_1)});
        /*
         * A quick note about read_result's structure:
         * success - bool, denotes the read operation's success value (duh)
         * buffer - std::vector<char>, the bytes from the read operation
         */

        if(res.success)
        {
            /*
             * Just an example of some of the reading we can do. Pass back a dummy echo message for now.
             * This is where a type parser should come in, rather than this switch statement.
             */
            auto messageType = *(res.buffer.begin());
            switch(messageType)
            {
                //case 'm':
            default:
                std::cout << "A client sent the follwing message: ";
                /*
                 * Better ways to handle this, including constructing a string from these iterators, but
                 * this is Milestone 1 - we're not even able to intergrate the protocol yet...
                 */
                for(auto i = res.buffer.begin()+1;i != res.buffer.end();i++)
                {
                    std::cout << *i;
                }
                std::cout << std::endl;
                std::stringstream resp;
                resp << "Message recieved. The packet had " << res.buffer.size() << " bytes in it.";
                // this is where the response would get transferred to the parser to be packaged and spat back out
                client->async_write({std::vector<char>{resp.str().begin(), resp.str().end()}, nullptr});
                break;
                /*default:
                std::cerr << "We couldn't tell what type of message the client sent." << std::endl;
                break;*/
            }
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

    s.start("127.0.0.1", 7331, [] (const std::shared_ptr<tacopie::tcp_client>& client) -> bool {
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
