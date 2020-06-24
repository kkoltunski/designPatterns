#include "commander.h"

//iCommander methods
iCommander::iCommander(directory* _folder) : folder{ _folder } {
}

void iCommander::reloadDestinationDirectory(directory* _newDirectory){
	folder = _newDirectory;
}

//fileCreator methods
fileCreator::fileCreator(directory* _folder) : iCommander{ _folder }{
}

bool fileCreator::doCommand(const LPCSTR& _name){
	bool result{ false };

	if(folder->isFileExisting()){
		iFile* pToFile = folder->tryToAddFileToDirectory(_name);

		if (pToFile != nullptr) {
			result = true;
		}
	}

	return result;
}


//directory creator methods
directoryCreator::directoryCreator(directory* _folder) : iCommander{ _folder } {
}

bool directoryCreator::doCommand(const LPCSTR& _name) {
	bool result{ false };

	if(folder->isFileExisting()){
		iFile* pToFile = folder->tryToAddFolderToDirectory(_name);

		if (pToFile != nullptr) {
			result = true;
		}
	}

	return result;
}

//fileRemover methods
fileRemover::fileRemover(directory* _folder) : iCommander{ _folder } {
}

bool fileRemover::doCommand(const LPCSTR& _name) {
	bool result{ false };
	iFile* pToFile{ nullptr };

	if(folder->isFileExisting()){
		pToFile = folder->searchForFile(_name);

		if (pToFile != nullptr) {
			result = pToFile->tryToRemove();
		}
	}

	return result;
}

//finisher methods
finisher::finisher() : iCommander{ nullptr }{
}

bool finisher::doCommand(const LPCSTR& _messageToShow) {
	bool result{ true };

	std::cout << _messageToShow << std::endl;

	return result;
}
