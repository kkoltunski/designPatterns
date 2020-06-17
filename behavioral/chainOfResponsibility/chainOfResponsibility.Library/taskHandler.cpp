#include "taskHandler.h"

void taskHandler::nextTaskAssigment(taskHandler* _nextTask) {
	if (nextTask == nullptr) {
		nextTask = _nextTask;
	}
	else {
		nextTask->nextTaskAssigment(_nextTask);
	}
}

void taskHandler::streamCleaning() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//Authenticator methods
authenticator::authenticator(accountsManagement* _accountManagment)
	: auxiliaryID(""), auxiliaryKey(""), globalAccountsManagment{ _accountManagment }, accountToAuthorize{ nullptr }{
}

void authenticator::getLogin() {
	bool streamError{ false };

	do {
		std::cout << "Type your login or enter \"0\" to cancel : ";
		std::cin >> auxiliaryID;

		if (globalAccountsManagment->isLoginUnique(auxiliaryID)) {
			std::cin.setstate(std::ios::failbit);
		}
		streamError = std::cin.fail();

		streamCleaning();

	} while (streamError && (auxiliaryID != "0"));

	if (auxiliaryID == "0") {
		auxiliaryID.clear();
	}
}

void authenticator::getPassword() {
	bool streamError{ false };

	do {
		std::cout << "Type your password or enter \"0\" to cancel : ";
		std::cin >> auxiliaryKey;

		if (!accountToAuthorize->isPasswordValid(auxiliaryKey)) {
			std::cin.setstate(std::ios::failbit);
		}
		streamError = std::cin.fail();

		streamCleaning();

	} while (streamError && (auxiliaryKey != "0"));

	if (auxiliaryKey == "0") {
		auxiliaryKey.clear();
	}
}

void authenticator::initializer() {
	accountToAuthorize = nullptr;
	auxiliaryID.clear();
	auxiliaryKey.clear();
}

taskHandler* authenticator::taskExecution() {
	taskHandler* result{ nullptr };
	getLogin();

	if (!auxiliaryID.empty()) {
		accountToAuthorize = globalAccountsManagment->getAccoutn(auxiliaryID);

		getPassword();

		if (!auxiliaryKey.empty()) {
			std::cout << "Authentication sucessfull.\n" << std::endl;
			result = nextTask;
		}
	}

	initializer();

	return result;
}

//Log builder methods
logBuilder::logBuilder(std::list<std::string>* const _archive, std::size_t _payloadDataLength)
	: pToLogArchive{ _archive }, payloadDataLength{ _payloadDataLength }, actualSystemTimestamp{}{
}

void logBuilder::getSystemTimestamp() {
	auto currentTime = std::chrono::system_clock::now();
	actualSystemTimestamp = std::chrono::system_clock::to_time_t(currentTime);
}

void logBuilder::getPayloadData() {
	bool streamError{ false };

	do {
		std::cout << "Introduce log palyload data or enter \"0\" to cancel.\n(Size have to be bigger than " << payloadDataLength << ") : ";

		std::getline(std::cin, payloadData);
		if (payloadData.size() <= payloadDataLength) {
			std::cin.setstate(std::ios::failbit);
		}

		streamError = std::cin.fail();
		std::cin.clear();

	} while (streamError && (payloadData != "0"));

	if (payloadData == "0") {
		payloadData.clear();
	}
}

std::string logBuilder::logMaker() {
	std::string timeBuffer("", 24), readyLog;

	ctime_s(&timeBuffer[0], sizeof timeBuffer, &actualSystemTimestamp);
	readyLog = timeBuffer + " : " + payloadData;

	return readyLog;
}

void logBuilder::initializer() {
	actualSystemTimestamp = 0;
	payloadData.clear();
}

taskHandler* logBuilder::taskExecution() {
	taskHandler* result{ nullptr };
	getPayloadData();

	if (!payloadData.empty()) {
		getSystemTimestamp();
		pToLogArchive->push_back(logMaker());
		result = nextTask;
	}

	initializer();

	return result;
}

//log saver methods
logSaver::logSaver(std::list<std::string>* const _archive, std::ofstream* const _istream)
	: pToLogArchive{ _archive }, pToFileStream{ _istream }, auxiliaryLog{ "" }{

}

void logSaver::getLogFromArchive() {
	auxiliaryLog = pToLogArchive->back();
}

bool logSaver::isFileReady() {
	bool result{ false };

	if (pToFileStream->is_open()) {
		if (pToFileStream->good()) {
			result = true;
		}
	}

	return result;
}

void logSaver::initializer() {
	auxiliaryLog.clear();
}

taskHandler* logSaver::taskExecution() {
	taskHandler* result{ nullptr };
	if (isFileReady()) {
		getLogFromArchive();
		auxiliaryLog += "\r\n";
		pToFileStream->write(&auxiliaryLog[0], auxiliaryLog.size());

		std::cout << "Log saved sucessfull.\n" << std::endl;
	}

	initializer();

	return result;
}