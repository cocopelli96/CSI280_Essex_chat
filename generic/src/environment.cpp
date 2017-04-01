#include <stdint.h>

#include "environment.h"
#include "message_handler.h"
#include "message.h"

Environment* Environment::environment = NULL;

Environment::Environment() {
	this->_outgoing = new MessageHandler();
	this->_incoming = new MessageHandler();
}

Environment::~Environment() {
	delete this->_outgoing;
	delete this->_incoming;
}

void Environment::createEnvironment

Environment* Environment::getEnvironment() {
	return environment;
}

void Environment::sendMessage(Message* message) {
	this->_outgoing->accept(message);
}

void Environment::sendMessage(uint16_t channel_id, uint16_t user_id, char* text) {
	this->_outgoing->accept(channel_id, user_id, text);
}
