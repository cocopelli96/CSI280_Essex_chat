#pragma once

#include <tacopie/tacopie>

#define ESSEX_PORT 7331

tacopie::tcp_client initNetcode(const std::string &addr);

void cleanupNetcode(tacopie::tcp_client &client);

void onMessageReceived(tacopie::tcp_client& client, const tacopie::tcp_client::read_result &result);
