#include "server_environment.hpp"
#include "channel.hpp"

ServerEnvironment::ServerEnvironment() : Environment() {
	//set up handlers...
}

ServerEnvironment::~ServerEnvironment() {
	//whatever
}

void ServerEnvironment::createServerEnvironment() {
	createEnvironment(new ServerEnvironment());
}

/*
 * @CalmBit I think you need to implement sendToUser
 */

void ServerEnvironment::sendToChannel(uint16_t channel_id, Message* message) {
	Channel* channel = Channel::getChannelIfExists(channel_id);
	if(!channel) return;
	for(auto user_id : channel->getUserIDs()) {
		this->sendToUser(user_id, message);
	}
}
