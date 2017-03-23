#include "command_names.h"

#define TRIGGER(t) do { current_trigger = t; } while(0)
#define NAME(n) do { handler->nameTrigger(n, current_trigger); } while(0)
#define CALLBACK(callback) do { handler->registerCallback(callback, current_trigger) } while (0)
#define SERVER_CALLBACK(callback) SERVER(CALLBACK(callback))
#define CLIENT_CALLBACK(callback) CLIENT(CALLBACK(callback))

#ifdef MODE_SERVER
	#define SERVER(...) do { __VA_ARGS__ } while(0)
	#define CLIENT(...) do { } while(0)
#else
	#define CLIENT(...) do { __VA_ARGS__ } while(0)
	#define SERVER(...) do { } while(0)
#endif

uint8_t current_trigger = 0;

void COMMANDS(MessageHandler* handler) {

/* EXAMPLE USAGE
TRIGGER(STANDARD_TRIGGER);
SERVER_CALLBACK(processServerMessage);
CLIENT_CALLBACK(processClientMessage);

TRIGGER('l');				//now we're configuring the 'l' command
NAME("login");				//this command is available as /login
SERVER_CALLBACK(serverLogin);		//marks a client as logged in and send a user ID (or error) back
CLIENT_CALLBACK(clientLogin);		//notes the user ID locally and updates the UI (or handle error)

TRIGGER('r');				//now we're configuring the 'r' command
NAME("register");			//this command is available as /register
SERVER_CALLBACK(serverRegister);	//checks the username for availability and blah
CLIENT_CALLBACK(invalidCommand);	//the server uses 'l' to acknowledge registration

TRIGGER('j');				//now we're configuring the 'j' command
NAME("join");				//this command is available as /join...
NAME("channel");			//...or /channel
SERVER_CALLBACK(serverJoinChannel);
CLIENT_CALLBACK(clientJoinChannel);

TRIGGER('0');				//numeric IDs are reserved for the client's internal use
NAME("help");
CLIENT_CALLBACK(showHelp);
SERVER_CALLBACK(invalidCommand);

TRIGGER('1');
NAME("exit");
CLIENT_CALLBACK(exit);
SERVER_CALLBACK(invalidCommand);
*/

}
