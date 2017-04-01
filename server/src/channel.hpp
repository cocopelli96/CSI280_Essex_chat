#ifndef CHANNEL_H
#define CHANNEL_H

#include <set>
#include <map>
#include <stdint.h>

class Channel {
private:
	std::set<uint16_t> _users;
public:
	const std::set<uint16_t>& getUserIDs();
	void addUser(uint16_t user_id);
	static Channel* getChannel(uint16_t channel_id);
	static Channel* getChannelIfExists(uint16_t channel_id);
};

#endif
