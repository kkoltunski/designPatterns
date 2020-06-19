#include "account.h"

template<typename T>
T generateRandomValueInRange(T _bottomRange, T _upperRange) {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(static_cast<int>(_bottomRange), static_cast<int>(_upperRange)); // define the range

	return static_cast<T>(distr(gen));
}

void userPassword::generatePassword() {
	short passwordSize = static_cast<short>(generateRandomValueInRange(accountParameterSettings::minSize, accountParameterSettings::maxSize));

	for (int i = 0; i < passwordSize; ++i) {
		password += static_cast<char>(generateRandomValueInRange(accountParameterSettings::lowestChar, accountParameterSettings::biggestChar));
	}

	//std::cout << password << std::endl;
}

bool account::isPasswordValid(const std::string& _passwordToValidate) {
	bool result{ true };

	if (key.password != _passwordToValidate) {
		result = false;
	}

	return result;
}

accountsManagement::~accountsManagement() {
	std::for_each(std::begin(authorizedAccounts), std::end(authorizedAccounts), [](account* pToAccount) { delete pToAccount; });
}

bool accountsManagement::isLoginCorrect(const std::string& _login) {
	bool result{ true };
	int typedLoginSize = _login.size();
	short castedMinSize = static_cast<short>(accountParameterSettings::minSize);
	short castedMaxSize = static_cast<short>(accountParameterSettings::maxSize);
	char castedLowestCharValue = static_cast<char>(accountParameterSettings::lowestChar);
	char castedBiggestCharValue = static_cast<char>(accountParameterSettings::biggestChar);

	if ((typedLoginSize < castedMinSize) || (typedLoginSize > castedMaxSize)) {
		result = false;
	}
	else {
		for (int i = 0; i < typedLoginSize; ++i) {
			char auxiliaryChar = _login[i];

			if ((auxiliaryChar < castedLowestCharValue) || (auxiliaryChar > castedBiggestCharValue)) {
				result = false;
				break;
			}
		}
	}

	return result;
}

void accountsManagement::addAccount(const std::string& _login) {
	try {
		if (!isLoginCorrect(_login)) {
			throw(std::exception("Login is not correct.\n"));
		}
		if (!isLoginUnique(_login)) {
			throw(std::exception("Login is existing already.\n"));
		}

		authorizedAccounts.push_back(new account(_login));
	}
	catch (std::exception& exception) {
		std::cout << exception.what() << std::endl;
	}
}

bool accountsManagement::isLoginUnique(const std::string& _loginToFind) {
	bool result{ true };
	std::function<bool(account*)> loginComparision = [&](account* pToAccount)
	{bool lambdaResult{ false }; if (pToAccount->getLogin() == _loginToFind) { lambdaResult = true; } return lambdaResult; };

	auto accountIterator = std::find_if(std::begin(authorizedAccounts), std::end(authorizedAccounts), loginComparision);

	if (accountIterator != std::end(authorizedAccounts)) {
		result = false;
	}

	return result;
}

account* accountsManagement::tryToGetAccoutn(const std::string& _loginToFind) {
	account* result{ nullptr };
	std::function<bool(account*)> loginComparision = [&](account* pToAccount)
	{bool lambdaResult{ false }; if (pToAccount->getLogin() == _loginToFind) { lambdaResult = true; } return lambdaResult; };

	auto accountIterator = std::find_if(std::begin(authorizedAccounts), std::end(authorizedAccounts), loginComparision);

	if (accountIterator != std::end(authorizedAccounts)) {
		result = (*accountIterator);
	}

	return result;
}