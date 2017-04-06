#include "message.h"
#include <string.h>
#include <cstdlib>

#define TRIGGER_SIZE 1
#define DATALEN_SIZE 2
#define CHANNEL_ID_SIZE 2
#define USER_ID_SIZE 2
#define HEADER_SIZE (TRIGGER_SIZE + DATALEN_SIZE + CHANNEL_ID_SIZE + USER_ID_SIZE)

Message::Message(const Message &copyOf) :
	_trigger(copyOf._trigger),
	_channel_id(copyOf._channel_id),
	_user_id(copyOf._user_id),
	_text(strdup(copyOf._text)),
	_text_len(copyOf._text_len){};

Message::Message(uint8_t trigger, uint16_t channel_id, uint16_t user_id, const char* text) :
	_trigger(trigger),
	_channel_id(channel_id),
	_user_id(user_id),
	_text(strdup(text)),
	_text_len(strlen(text)) {};

Message::Message(uint8_t trigger, uint16_t channel_id, uint16_t user_id, const char* text, uint16_t text_len) :
	_trigger(trigger),
	_channel_id(channel_id),
	_user_id(user_id),
	_text((char*)malloc(text_len) + 1),
	_text_len(text_len) {
		memcpy(this->_text, text, text_len);	
		this->_text[text_len] = 0;
	};

Message::~Message() {
	free(this->_text);
}

uint8_t Message::getTrigger() const {
	return this->_trigger;
}

uint16_t Message::getChannelID() const {
	return this->_channel_id;
}

uint16_t Message::getUserID() const {
	return this->_user_id;
}

char const* Message::getText() const {
	return this->_text;
}

uint16_t Message::getSerialBufSize() const {
	return this->_text_len + HEADER_SIZE;
}

char* Message::toSerialForm(char* buf) const {
	buf[0] = this->_trigger;
	memcpy(buf + 1, &this->_text_len, 2);
	memcpy(buf + 3, &this->_user_id, 2);
	memcpy(buf + 5, &this->_channel_id, 2);
	memcpy(buf + 7, this->_text, this->_text_len);
}

Message* Message::fromSerialForm(char* serial_form, signed int tcp_length) {
	uint16_t text_len = *((uint16_t*)(serial_form + 1));
	if(tcp_length && (text_len + HEADER_SIZE != tcp_length)) return NULL;
	uint16_t user_id = *((uint16_t*)(serial_form + 3));
	uint16_t channel_id = *((uint16_t*)(serial_form + 5));
	uint8_t trigger = serial_form[0];
	return new Message(trigger, channel_id, user_id, serial_form + HEADER_SIZE, text_len);
}