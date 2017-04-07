#include <stdint.h>

#include "environment.h"
#include "message_handler.h"
#include "message.h"

Environment* Environment::environment = NULL;

Environment::Environment() { }

Environment::~Environment() { }

void Environment::createEnvironment(Environment* new_environment) {
	environment = new_environment;
}

Environment* Environment::getEnvironment() {
	return environment;
}

void Environment::sendMessage(const Message* message) {
	this->outgoing.accept(message);
}

void Environment::sendMessage(uint16_t channel_id, uint16_t user_id, char* text) {
	this->outgoing.accept(channel_id, user_id, text);
}
