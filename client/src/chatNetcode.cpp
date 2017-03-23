#include "chatNetcode.hpp"

#include <iostream>

void initNetcode(tacopie::tcp_client &client, const std::string &addr)
{
    client.connect(addr, ESSEX_PORT);
    client.async_read({ 1024, std::bind(&onMessageReceived, std::ref(client), std::placeholders::_1) });
}

void writeToServer(tacopie::tcp_client &client, const std::string &message)
{
    std::vector<char> messageVector{message.begin(), message.end()};
    client.async_write({messageVector, nullptr});
}

void cleanupNetcode(tacopie::tcp_client &client)
{
    client.disconnect();
}

void onMessageReceived(tacopie::tcp_client& client, const tacopie::tcp_client::read_result &result)
{
    // travis should place some required code for ncurses interaction here, or whatever
    // parsing we'll need to do
}
