#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stdint.h>

#include "message_handler.h"

class Environment {
private:
	static Environment* environment;
protected:
	Environment();
	~Environment();
	MessageHandler outgoing;
	MessageHandler incoming;
	static void createEnvironment(Environment* environment);
public:
	static Environment* getEnvironment();
	void sendMessage(const Message* message);
	void sendMessage(uint16_t channel_id, uint16_t user_id, char* text);
};

#endif
