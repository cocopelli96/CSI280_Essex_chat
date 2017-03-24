#include "placeholder.h"

#include "message.h"
#include "message_handler.h"

#include <stdio.h>

char* getUsername(const char* local_username, int user_id) {
	static char buf[50];
	if(user_id) {
		return snprintf(buf, 50, "User%d", user_id);
	} else {
		return snprintf(buf, 50, local_username);
	}
}

int getColorID(int user_id) {
	return user_id ? 2 : 3;
}

void fakeServer(const Message* message, MessageHandler* handler) {
	handler->accept(message);
}
