#ifndef TASKHANDLER_H
#define TASKHANDLER_H

#include <limits> 
#include <chrono>
#include <ctime> 
#include <fstream>
#include "account.h"

class taskHandler {
protected:
	void streamCleaning();
	virtual void initializer() = 0;
	taskHandler* nextTask;

public:
	taskHandler() : nextTask{ nullptr } {
	}
	virtual ~taskHandler() = default;

	void nextTaskAssigment(taskHandler* _nextTask);
	virtual taskHandler* taskExecution() = 0;
};

class authenticator : public taskHandler {
private:
	void getLogin();
	void getPassword();
	virtual void initializer() override;

	std::string auxiliaryID;
	std::string auxiliaryKey;

	accountsManagement* const globalAccountsManagment;
	account* accountToAuthorize;

public:
	authenticator(accountsManagement* _accountManagment);
	virtual taskHandler* taskExecution() override;
};

class logBuilder : public taskHandler {
private:
	void getSystemTimestamp();
	void getPayloadData();
	std::string logMaker();
	virtual void initializer() override;

	std::time_t actualSystemTimestamp;
	std::size_t payloadDataLength;
	std::string payloadData;

	std::list<std::string>* const pToLogArchive;

public:
	logBuilder(std::list<std::string>* const _archive, std::size_t _payloadDataLength);
	virtual taskHandler* taskExecution() override;
};

class logSaver : public taskHandler {
private:
	bool isFileReady();
	void getLogFromArchive();
	virtual void initializer() override;

	std::list<std::string>* const pToLogArchive;
	std::ofstream* const pToFileStream;

	std::string auxiliaryLog;

public:
	logSaver(std::list<std::string>* const _archive, std::ofstream* const _istream);
	virtual taskHandler* taskExecution() override;
};
#endif // TASKHANDLER_H