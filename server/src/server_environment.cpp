#include "server_environment.hpp"
#include "channel.hpp"
#include "message_handler.h"
#include "message.h"

#include <stdexcept>
#include <sstream>

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

static void userLogin(const Message* message) {

}

static void userRegister(const Message* message) {
	
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
	
	this->incoming.registerCallback(loopback, STANDARD_TRIGGER);
	this->outgoing.registerCallback(relayMessage, DEFAULT_TRIGGER);

	this->incoming.registerCallback(joinChannel, 'j');
	this->incoming.registerCallback("join", 'j');

	this->incoming.registerCallback(userLogin, 'L');
	this->incoming.nameTrigger("login", 'L');

	this->incoming.registerCallback(userRegister, 'R');
	this->incoming.nameTrigger("register", 'R');
}

ServerEnvironment::~ServerEnvironment() {
	//whatever
}

void ServerEnvironment::createServerEnvironment(tacopie::tcp_server *server) {
	this->server_ptr = std::shared_ptr<tacopie::tcp_server>{server};
	createEnvironment(&env);
}

void ServerEnvironment::sendToUser(uint16_t user_id, Message* message) {
	std::shared_ptr<tacopie::tcp_client> client = this->getUser(user_id);
	if(client == nullptr)
	{
		stringstream err{};
		err << "user_id " << user_id << " doesn't exist - cannot send message";
		throw std::invalid_argument{err.str()};
	}
	auto bf_sz = message->getSerialBufSize();
	char* buffer = new char[buf_sz];
	client.async_write({std::vector<char>{buffer, buffer+buf_sz}, nullptr});
}

/*
 * Gets a user connection (specifically a shared_ptr of a client object) by user ID. 
 * If no matching connection is found, returns a nullptr, otherwise returns a shared_ptr
 * to the client object.
 */
std::shared_ptr<tacopie::tcp_client> ServerEnvironment::getUser(uint16_t user_id)
{
	try
	{
		return this->client_list.at(user_id);
	}
	catch(std::out_of_range &e)
	{
		// We can safely assume that since we're getting an out of range
		// exception, there's nothing going on aside from a lack of the
		// value we're looking for, so quashing this exception is okay...
		return nullptr;
	}
}

/*
 * Adds a user to the client_list object.
 * Throws an std::invalid_argument exception if the user_id is already registered,
 * otherwise adds the user_id to the client_list map.
 */ 
void ServerEnvironment::addUser(uint16_t user_id, std::shared_ptr<tacopie::tcp_client> connection)
{
	// Do we have a connection by this user_id already? Throw it away,
	// throw an exception.
	if(this->client_list.find(user_id) != this->client_list.end())
	{
		stringstream err{};
		err << "user_id " << user_id << " is already registered";
		throw std::invalid_argument{err.str()};
	}

	// Otherwise, just add it to the map.
	this->client_list[user_id] = connection;
}

/*
 * Remove a user from the client_list object.
 * If the user specified doesn't exist, throws an std::invalid_argument exception,
 * otherwise completely erases the entry from the map.
 */ 
void ServerEnvironment::removeUser(uint16_t user_id)
{
	// If we can't find a matching connection, we should throw an exception -
	// otherwise, we'd get undefined behaviour.
	if(this->client_list.find(user_id) == this->client_list.end())
	{
		stringstream err{};
		err << "user_id " << user_id << " doesn't exist - cannot be removed";
		throw std::invalid_argument{err.str()};
	}

	// Otherwise, erase the connection.
	this->client_list.erase(user_id);
}


void ServerEnvironment::sendToChannel(Message* message) {
	Channel* channel = Channel::getChannelIfExists(message->getChannelID());
	if(!channel) return;
	for(auto user_id : channel->getUserIDs()) {
		this->sendToUser(user_id, message);
	}
}


void ServerEnvironment::recieveFromClient(const std::shared_ptr<tacopie::tcp_client>& client, const tacopie::tcp_client::read_result& res)
{
  if(res.success)
  {
    std::cout << "Our client sent something!" << std::endl;
    client->async_read({1024, std::bind(&recieveFromClient, client, std::placeholders::_1)});
    /*
     * A quick note about read_result's structure:
     * success - bool, denotes the read operation's success value (duh)
     * buffer - std::vector<char>, the bytes from the read operation
     */

  }
}
