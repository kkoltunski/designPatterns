#include "header.h"

int main(int argc, const char* argv[]){
	argc = 4;
	argv[0] = R"(PROXY design pattern)";
	argv[1] = R"(C:\Users\kkoltunski\Desktop\Klaudiusz Ko³tuñski\NAUKA\C++\00_Projects\00_Real\00_VisualStudio\designPatterns\structurals\proxy\settings.txt)";
	argv[2] = R"(1.2)";
	argv[3] = R"(absolute)";

	if(passedArgumentsNumberCorrect(argc)){
		programConfigFile::createInstance(argc, argv);
		programConfigFileProtectionProxy protectionProxyConfigFile(programConfigFile::getInstance());

		protectionProxyConfigFile.readParameter(0);
		protectionProxyConfigFile.readParameter(1);
		protectionProxyConfigFile.readParameter(2);
		protectionProxyConfigFile.readParameter(3);
		protectionProxyConfigFile.readParameter(4);
		protectionProxyConfigFile.writeParameter("Parameter introduced by proxy guard", 2);

		programConfigFile::getInstance().readParameter(0);
		programConfigFile::getInstance().readParameter(1);
		programConfigFile::getInstance().readParameter(2);
		programConfigFile::getInstance().readParameter(3);
		programConfigFile::getInstance().readParameter(4);
		programConfigFile::getInstance().writeParameter("Parameter introduced direct", 1);
	}

	return 0;
}
