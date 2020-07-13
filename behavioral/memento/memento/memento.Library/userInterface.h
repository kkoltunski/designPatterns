#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "settingsMemento.h"
#include "settings.h"

class userInterface{
private:
	settings* pToSettings;
	settingsMemento* pToMemento;

public:
	userInterface(settings* _pToSettings);

	void showOptions();
};

#endif // USERINTERFACE_H