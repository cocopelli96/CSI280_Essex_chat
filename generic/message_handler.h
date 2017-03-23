#ifndef _MESSAGE_HANDLER_H_
#define _MESSAGE_HANDLER_H_

#include <stdint.h>
#include <map>
#include <cstring>

#include "message.h"

#define DEFAULT_TRIGGER 0	//the trigger to use if none match
#define STANDARD_TRIGGER 'm'	//the trigger to use for a normal message (ie. no initial / )
#define COMMAND_CHARACTER '/'

typedef void(*MessageCallback)(const Message* message);

struct cmpcharp {
	bool operator()(char const* a, char const* b) const {
		return std::strcmp(a, b) < 0;
	}
};

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
