#include "commandInvoker.h"

void commandInvoker::addMissingPositions(std::size_t _missingPositions){
	for (std::size_t i = 0; i < _missingPositions; ++i) {
		commands.push_back(nullptr);
	}
}

std::list<iCommander*>::const_iterator commandInvoker::findIterator(std::size_t _index){
	std::list<iCommander*>::const_iterator wantedIterator = commands.begin();

	if(_index > 0){
		for (std::size_t i = 0; i < _index; ++i, ++wantedIterator) {}
	}

	return wantedIterator;
}

void commandInvoker::addCommand(std::size_t _index, iCommander* _commandToAdd){
	std::size_t absoluteCommandsListSize = (commands.size() - 1);

	if(_index > absoluteCommandsListSize){
		size_t missingPositions{ _index - absoluteCommandsListSize };
		addMissingPositions(missingPositions);
	}

	auto indexIterator = findIterator(_index);
	commands.insert(indexIterator, _commandToAdd);
}

bool commandInvoker::callCommand(std::size_t _index, const std::string &_fileName){
	bool result{ false };
	std::size_t absoluteCommandsListSize = (commands.size() - 1);
	iCommander* pToCommand{ nullptr };

	if(_index < absoluteCommandsListSize){
		pToCommand = (*findIterator(_index));

		if(pToCommand != nullptr){
			result = pToCommand->doCommand(static_cast<LPCSTR>(_fileName.c_str()));
		}
	}

	return result;
}

void commandInvoker::reloadDirectory(directory* _newDestinationDirectory){
	std::function <void(iCommander*)> reloadDestinationDirectory = [&](iCommander* pToCommand)
	{if (pToCommand != nullptr) { pToCommand->reloadDestinationDirectory(_newDestinationDirectory); }};

	std::for_each(std::begin(commands), std::end(commands), reloadDestinationDirectory);
}

std::string commandInvoker::commandDescriptionSelector(iCommander* _commandToCheck){
	std::string commandDescription{""};

	if(dynamic_cast<fileCreator*>(_commandToCheck)){
		commandDescription = "to create file.";
	}
	else if (dynamic_cast<directoryCreator*>(_commandToCheck)) {
		commandDescription = "to create directory.";
	}
	else if (dynamic_cast<fileRemover*>(_commandToCheck)) {
		commandDescription = "to remove file/directory.";
	}
	else if (dynamic_cast<finisher*>(_commandToCheck)) {
		commandDescription = "to finish.";
	}

	return commandDescription;
}

void commandInvoker::showPossibilities(){
	std::size_t index{ 0 };

	system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	std::cout << "Choose: " << std::endl;

	for(auto commandIterator = std::begin(commands); commandIterator != commands.end(); ++commandIterator, ++index){
		iCommander* pToCommand = (*commandIterator);

		if(pToCommand != nullptr){
			std::cout << index << ") " << commandDescriptionSelector(pToCommand) << std::endl;
		}
	}
}