#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#define KEY_UP    72
#define KEY_DOWN  80
#define KEY_ENTER 10

#include <conio.h>
#include <vector>
#include "settingsMemento.h"
#include "settings.h"

class userInterface{
private:
	enum magicNumbers { offsetToFirstElement = 2 };

	void selectorValueControl();
	void updateProfileList();

	settings* pToSettings;
	settingsMemento* pToMemento;
	std::list<std::string> profileNames;
	std::vector<std::string> optionsVector;

	int selector;
	int choosenProfileNameIndex;
	bool update;
public:
	userInterface(settings* _pToSettings);

	void showProfileNamesContentInConsole();
	void showOptionsVectorInConsole();
	void saveOrder();
	void loadOrder();
	void getKey();
};

#endif // USERINTERFACE_H