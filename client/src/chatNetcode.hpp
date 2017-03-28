#pragma once

#include <tacopie/tacopie>

#define ESSEX_PORT 7331

void initNetcode(tacopie::tcp_client &client, const std::string &addr);

void writeToServer(tacopie::tcp_client &client, const std::string &message);

void cleanupNetcode(tacopie::tcp_client &client);

void onMessageReceived(tacopie::tcp_client& client, const tacopie::tcp_client::read_result &result);
