#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <stdint.h>

class Account {
private:
	const char* _username;
	const uint16_t _user_id;
	Account(char* username);
	~Account();
public:
	const char* getUsername();
	static Account* getAccountIfExists(char* username);
	static Account* getAccountIfExists(uint16_t user_id);
	static Account* createAccount(char* username);
};

#endif
