#ifndef COMMANDINVOKER_H
#define COMMANDINVOKER_H

#include "commander.h"

class commandInvoker{
private:
	void addMissingPositions(std::size_t _missingPositions);
	std::list<iCommander*>::const_iterator findIterator(std::size_t _index);
	std::string commandDescriptionSelector(iCommander* _commandToCheck);

	std::list<iCommander*> commands;

public:
	void addCommand(std::size_t _index, iCommander* _commandToAdd);
	bool callCommand(std::size_t _index, const std::string& _fileName);
	void reloadDirectory(directory* _newDestinationDirectory);
	void showPossibilities();
};

#endif // COMMANDINVOKER_H