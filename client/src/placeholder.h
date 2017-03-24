#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

//#include "../../generic/message.h"
//#include "../../generic/message_handler.h"
#include "message.h"
#include "message_handler.h"

char* getUsername(const char* local_username, int user_id);

int getColorID(int user_id);

void fakeServer(const Message* message, MessageHandler* handler);

#endif
