#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <stdint.h>
#include <string>

class Message {

private:
	const uint8_t _trigger;
	const uint16_t _channel_id;
	const uint16_t _user_id;
	const uint16_t _text_len;
	char* _text;
public:
	Message(const Message &copyOf);
	Message(uint8_t trigger, uint16_t channel_id, uint16_t user_id, const char* text);
	Message(uint8_t trigger, uint16_t channel_id, uint16_t user_id, const char* text, uint16_t text_len);
	~Message();
	uint8_t getTrigger() const;
	uint16_t getChannelID() const;
	uint16_t getUserID() const;
	char const* getText() const;
	char* toSerialForm(char* buf) const;
	uint16_t getSerialBufSize() const;
	static Message* fromSerialForm(char* serial_form, signed int tcp_length);
};

#endif
