#include "server_environment.hpp"
#include "channel.hpp"
#include "message_handler.h"
#include "message.h"

static ServerEnvironment env;

static void loopback(const Message* message) {
	env.sendMessage(message);
}

static void relayMessage(const Message* message) {
	env.sendToChannel(message);
}

static void joinChannel(const Message* message) {
	uint16_t channel_id = message->getChannelID();
	//TODO: we should actually parse out the channel NAME from
	//the message body and use that if present
	uint16_t user_id = message->getUserID();
	Channel.getChannel(channel_id)->addUser(user_id);
}

ServerEnvironment::ServerEnvironment() : Environment() {
	//you'll need to implement the following handlers for issue 23:

	//incoming handlers:
	//	L : attempts to find an account by username, send its user ID back,
	//	    and associate that account with that user ID (you'll need to
	//	    write that functionality since I'm not sure how tacopie does connections)
	//	R : as L, except it creates an account instead of looking one up
	//	    see the issue for details on both of these
	//	    and account.h for details on account management
	//
	//outgoing handlers:
	//	none, I've done this as an example
	
	this->incoming.registerHandler(loopback, STANDARD_TRIGGER);
	this->outgoing.registerHandler(relayMessage, DEFAULT_TRIGGER);

	this->incoming.registerHandler(joinChannel, 'j');
	this->incoming.nameTrigger("join", 'j');
}

ServerEnvironment::~ServerEnvironment() {
	//whatever
}

void ServerEnvironment::createServerEnvironment() {
	createEnvironment(&env);
}

/*
 * @CalmBit I think you need to implement sendToUser
 */

void ServerEnvironment::sendToChannel(Message* message) {
	Channel* channel = Channel::getChannelIfExists(message->getChannelID());
	if(!channel) return;
	for(auto user_id : channel->getUserIDs()) {
		this->sendToUser(user_id, message);
	}
}
