#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <stdint.h>
#include <map>
#include <cstring>

#include "message.h"
#include "cmpcharp.h"

#define DEFAULT_TRIGGER 0	//the trigger to use if none match
#define STANDARD_TRIGGER 'm'	//the trigger to use for a normal message (ie. no initial / )
#define COMMAND_CHARACTER '/'

typedef void(*MessageCallback)(const Message* message);

class MessageHandler {
private:
	MessageCallback _callbacks[256];
	std::map<char const*, uint8_t, cmpcharp> _command_names;
public:
	MessageHandler();
	void accept(const Message* message) const;
	void accept(uint16_t channel_id, uint16_t user_id, char const* text) const;
	void registerCallback(MessageCallback callback, uint8_t trigger);
	void nameTrigger(char const* name, uint8_t trigger);
};

#endif
