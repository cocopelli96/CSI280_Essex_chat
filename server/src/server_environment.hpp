#ifndef SERVER_ENVIRONMENT_H
#define SERVER_ENVIRONMENT_H

#include "environment.h"
#include "message.h"

class ServerEnvironment : public Environment {
private:
	ServerEnvironment();
	~ServerEnvironment();
public:
	/**
	 * Sets up a server environment. Subsequent calls to Environment::getEnvironment()
	 * will return this environment.
	 */
	static void createServerEnvironment();
	void sendToUser(uint16_t user_id, Message* message);
	void sendToChannel(Message* message);
};

#endif
