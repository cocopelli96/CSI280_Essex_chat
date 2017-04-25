#include "chatNetcode.hpp"
#include "chatUI.hpp"
#include <vector>


void cleanupNetcode(tacopie::tcp_client &client)
{
    client.disconnect();
}


void initNetcode(tacopie::tcp_client &client, const std::string &addr)
{
    client.connect(addr, ESSEX_PORT);
    client.async_read({ 1024, std::bind(&onMessageReceived, std::ref(client), std::placeholders::_1) });
}


void onMessageReceived(tacopie::tcp_client& client, const tacopie::tcp_client::read_result &result)
{
    std::vector<char> result_vec = result.buffer;
    int len = result_vec.size();
    char buf[len + 1];
    memcpy(buf, result_vec.data(), len);
    buf[len] = 0;
    addChatLine("<user>", buf, 3);
    addChatLine("<user>", "<message>", 3);
    client.async_read({ 1024, std::bind(&onMessageReceived, std::ref(client), std::placeholders::_1) });
}


void writeToServer(tacopie::tcp_client &client, const std::string &message)
{
    std::vector<char> messageVector{message.begin(), message.end()};
    client.async_write({messageVector, nullptr});
}
