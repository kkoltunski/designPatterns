#include "header.h"

int main(){
	std::string pathToFile = R"(C:\Users\kkoltunski\Desktop\Klaudiusz Ko³tuñski\NAUKA\C++\00_Projects\00_Real\00_VisualStudio\designPatterns\behavioral\chainOfResponsibility\logger.txt)";
	std::ofstream stramToFile(pathToFile, std::ios::out | std::ios::app | std::ios::ate | std::ios::binary);
	accountsManagement manager;
	authenticator* pToAuthenticator = new authenticator(&manager);
	logBuilder* pToLogBuilder = new logBuilder(&internalLogArchive, 15);
	logSaver* pToLogSaver = new logSaver(&internalLogArchive, &stramToFile);
	taskHandler* logHandler = pToAuthenticator;

	manager.addAccount("Klaudek24");
	manager.addAccount("Mini1999");
	manager.addAccount("randomMan");
	manager.addAccount("randomMan11");

	logHandler->nextTaskAssigment(pToLogBuilder);
	logHandler->nextTaskAssigment(pToLogSaver);

	do{
		logHandler = logHandler->taskExecution();
	} while (logHandler != nullptr);

	for(auto x : internalLogArchive){
		std::cout << x << std::endl;
	}

	delete pToAuthenticator, pToLogBuilder, pToLogSaver;
	return 0;
}