#include <map>
#include <vector>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <stdexcept>

#include "account.hpp"
#include "cmpcharp.h"

static std::map<char*, Account*, cmpcharp> _accounts;
static std::vector<Account*> _accounts_by_id;

Account::Account(uint16_t user_id, const char* username) {
	this->_user_id = user_id;
	size_t len = strlen(username);
	this->_username = new char[len];
	strcpy(this->_username, username);
}

Account::~Account() {
	delete this->_username;
}

const char* Account::getUsername() {
	return this->_username;
}

uint16_t Account::getUserID() {
	return this->_user_id;
}

Account* Account::getAccountIfExists(char* username) {
	return _accounts[username];
}

Account* Account::getAccountIfExists(uint16_t user_id) {
	return _accounts_by_id[user_id];
}

Account* Account::createAccount(char* username) {
	if(_accounts[username]) {
		throw new std::invalid_argument("duplicate username...");
	}
	uint16_t user_id = (uint16_t)_accounts_by_id.size();
	Account* account = new Account(user_id, username);
	_accounts_by_id[user_id] = account;
	_accounts[username] = account;
}
