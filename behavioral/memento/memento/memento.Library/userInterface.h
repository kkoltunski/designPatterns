#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#define KEY_UP    72
#define KEY_DOWN  80
#define KEY_ENTER '\r'

#include <conio.h>
#include <vector>
#include <limits>
#include "settingsMemento.h"
#include "settings.h"
#include "limit.h"

class userInterface{
private:
	enum control : char { optionControl = 0, profileControl = 1	};

	void showProfileNamesContentInConsole();
	void selectorValueControl();
	void updateProfileList();
	std::string getUserType();
	void saveOrder();
	void loadOrder();

	settings* pToSettings;
	settingsMemento* pToMemento;
	std::list<std::string> profileNames;
	std::vector<std::string> optionsVector;

	int optionSelector;
	int profileNameIndex;
	control actualControl;
	char pressedKey{};

public:
	userInterface(settings* _pToSettings);

	void showOptionsVectorInConsole();
	void actionPerformance();
	void keyFilter();
};

#endif // USERINTERFACE_H