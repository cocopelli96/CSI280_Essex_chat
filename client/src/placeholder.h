#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

#include "message.h"
#include "message_handler.h"

char* getUsername(char* local_username, int user_id);

int getColorID(int user_id);

void fakeServer(Message* message, MessageHandler* handler);

#endif
