#include "placeholder.h"

//#include "../../generic/message.h"
//#include "../../generic/message_handler.h"
#include "message.h"
#include "message_handler.h"

#include <stdio.h>

char* getUsername(const char* local_username, int user_id) {
	static char buf[50];
    char tmp;
    
	if(user_id) {
		tmp = snprintf(buf, 50, "User%d", user_id);
	} else {
		tmp = snprintf(buf, 50, "%s", local_username);
	}
    
    return &tmp;
}

int getColorID(int user_id) {
	return user_id ? 2 : 3;
}

void fakeServer(const Message* message, MessageHandler* handler) {
	handler->accept(message);
}
