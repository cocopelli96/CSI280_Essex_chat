#ifndef SERVER_ENVIRONMENT_H
#define SERVER_ENVIRONMENT_H

#include <map>
#include "environment.h"
#include "message.h"

class ServerEnvironment : public Environment {
private:
	ServerEnvironment();
	~ServerEnvironment();

	// Tacopie's tcp_server includes a list of client pointers, but it doesn't associate them to any value,
	// so we'll create a map to handle the association and use it instead.
	std::map<uint16_t, std::shared_ptr<tacopie::tcp_client>> client_list;
public:
	/**
	 * Sets up a server environment. Subsequent calls to Environment::getEnvironment()
	 * will return this environment.
	 */
	static void createServerEnvironment();
	void sendToUser(uint16_t user_id, Message* message);
	void sendToChannel(Message* message);
	
	std::shared_ptr<tacopie::tcp_client> getUser(uint16_t user_id);
	void addUser(uint16_t user_id, std::shared_ptr<tacopie::tcp_client> connection);
	void removeUser(uint16_t user_id);
};

#endif
