#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <string>
#include <random>
#include <list>
#include <algorithm>
#include <functional>
#include <exception>

enum class accountParameterSettings : char { minSize = 1/*8*/, maxSize = 5/*32*/, lowestChar = '!', biggestChar = '~' };

class userLogin{
private:
	userLogin(const std::string& _login) : login{ _login }{
	}

	std::string login;

	friend class account;
};

class userPassword{
private:
	userPassword() : password{ "" } {
		generatePassword();
	}
	void generatePassword();

	std::string password;

	friend class account;
};

class account {
private:
	userLogin ID;
	userPassword key;

public:
	account(const std::string& _login) : ID{ _login }, key{}{
	}
	inline std::string getLogin(){
		return ID.login;
	}
	bool isPasswordValid(const std::string& _passwordToValidate);
};

class accountsManagement{
private:
	bool isLoginCorrect(const std::string& _login);

	std::list<account*> authorizedAccounts;

public:
	accountsManagement() = default;
	virtual ~accountsManagement();

	void addAccount(const std::string& _login);
	bool isLoginUnique(const std::string& _loginToFind);
	account* getAccoutn(const std::string& _loginToFind);
};

#endif // STRUCTURES_H
