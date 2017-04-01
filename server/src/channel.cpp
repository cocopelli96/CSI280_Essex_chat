#include <set>
#include <stdint.h>

#include "channel.hpp"

static std::map<uint16_t, Channel*> _channels;

const std::set<uint16_t>& Channel::getUserIDs() {
	return this->_users;
}

void Channel::addUser(uint16_t user_id) {
	this->_users.insert(user_id);
}

Channel* getChannel(uint16_t channel_id) {
	Channel* channel = _channels[channel_id];
	if(channel == NULL) {
		channel = new Channel();
		_channels[channel_id] = channel;
	}
	return channel;
}

Channel* getChannelIfExists(uint16_t channel_id) {
	return _channels[channel_id];
}
