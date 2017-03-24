#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <stdio.h>

#include "message_handler.h"

MessageHandler::MessageHandler() {
	memset(this->_callbacks, 0, 256 * sizeof(this->_callbacks[0]));
}

void MessageHandler::accept(const Message* message) const {
	uint8_t trigger = message->getTrigger();
	MessageCallback callback = this->_callbacks[trigger];
	if(!callback) {
		callback = this->_callbacks[DEFAULT_TRIGGER];
	}
	if(callback) {
		callback(message);
	} else {
		throw std::invalid_argument("unknown callback and no default callback registered");
	}
}

void MessageHandler::accept(uint16_t channel_id, uint16_t user_id, char const* text) const {
	uint16_t trigger;
	size_t len = strlen(text) + 1;
	char* text2 = new char[len];
	memcpy(text2, text, len);
	char* freeme = text2;
	if(text2[0] == COMMAND_CHARACTER) {
		char* command_name = (text2 + 1);
		while(text2[0] && text2[0] != ' ') {
			++text2;
		}
		if(text2[0]) {
			text2[0] = 0;
			++text2;
		}
		if(this->_command_names.count(command_name)) {
			trigger = this->_command_names.at(command_name);
		} else {
			trigger = DEFAULT_TRIGGER;
		}
	} else {
		trigger = STANDARD_TRIGGER;
	}
	Message m(trigger, channel_id, user_id, text2);
	accept(&m);
	delete[] freeme;
}

void MessageHandler::registerCallback(MessageCallback callback, uint8_t trigger) {
	if(this->_callbacks[trigger]) {
		throw std::invalid_argument("callback already registered");
	}
	this->_callbacks[trigger] = callback;
}

void MessageHandler::nameTrigger(char const* name, uint8_t trigger) {
	this->_command_names[name] = trigger;
}
