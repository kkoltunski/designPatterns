#include "header.h"

int main(){
	std::string filePath = R"(C:\Users\kkoltunski\Desktop\Klaudiusz Ko³tuñski\NAUKA\C++\00_Projects\00_Real\00_VisualStudio\designPatterns\behavioral\strategy\createdFile.txt)";

	auto pToUpperConverter = new filestreamToUpper;
	auto pToLowerConverter = new filestreamToLower;
	auto pToSeparator = new filestreamSeparator('~');

	//Saving content to file
	std::string toSaveInFile = filePath + "\r\n";
	int toSaveSize = toSaveInFile.size();
	char* toSaveContent = new char[toSaveSize];

	for(int i = 0; i < toSaveSize; ++i){
		toSaveContent[i] = toSaveInFile[i];
	}

	boostedFstream file(filePath, std::ios::in | std::ios::out | std::ios::app);
	file.write(toSaveContent, toSaveSize);
	file.changeOpenedMode(std::ios::in | std::ios::out | std::ios::ate);

	//Strategy design pattern useage
	filestreamFormater formater{ file };
	formater.operation(pToUpperConverter);
	formater.operation(pToLowerConverter);
	formater.operation(pToSeparator);

	delete pToUpperConverter, pToLowerConverter, pToSeparator;
	return 0;
}