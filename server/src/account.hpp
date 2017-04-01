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

	/**
	 * Returns the account with some username, or null if it doesn't exist.
	 */
	static Account* getAccountIfExists(char* username);

	/**
	 * Returns the account with some user ID, or null if it doesn't exist.
	 */
	static Account* getAccountIfExists(uint16_t user_id);

	/**
	 * Creates an account with a given username, or null if the account
	 * can't be created (eg. if an account with that name already exists).
	 */
	static Account* createAccount(char* username);
};

#endif
