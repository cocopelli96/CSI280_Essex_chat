#ifndef chatNetCode_hpp
#define chatNetCode_hpp

#include <iostream>
#include <tacopie/tacopie>

#define ESSEX_PORT 7331


void cleanupNetcode(tacopie::tcp_client &client);
void initNetcode(tacopie::tcp_client &client, const std::string &addr);
void onMessageReceived(tacopie::tcp_client& client, const tacopie::tcp_client::read_result &result);
void writeToServer(tacopie::tcp_client &client, const std::string &message);


#endif
