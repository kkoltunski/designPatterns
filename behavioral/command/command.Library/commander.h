#ifndef COMMANDER_H
#define COMMANDER_H

#include "directory.h"

class iCommander{
protected:
	directory* folder;

public:
	explicit iCommander(directory* _folder);
	virtual bool doCommand(const LPCSTR& _name) = 0;
	void reloadDestinationDirectory(directory* _newDirectory);
};

class fileCreator : public iCommander{
public:
	explicit fileCreator(directory* _folder);
	virtual bool doCommand(const LPCSTR& _name) override;
};

class directoryCreator : public iCommander {
public:
	explicit directoryCreator(directory* _folder);
	virtual bool doCommand(const LPCSTR& _name) override;
};

class fileRemover : public iCommander {
public:
	explicit fileRemover(directory* _folder);
	virtual bool doCommand(const LPCSTR& _name) override;
};

class finisher : public iCommander {
public:
	explicit finisher();
	virtual bool doCommand(const LPCSTR& _messageToShow) override;
};


#endif // COMMANDER_H