#ifndef USERINTARFACE_H
#define USERINTERFACE_H

#define POSSIBLE_EVENTS 2
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
constexpr const char* eventsNames[] = { "timer", "mouse press" };

#include "mediator.h"
#include <iostream>
#include <thread>
#include <conio.h>

class userInterface{
private:
	userInterface();
	void backendLoop();
	void uglySwitch(int _option);
	void currentlyPointedControl();
	void choosenOptionChange();

	int m_currentlyPointed;
	bool m_currentlyPointedChange;
	int m_choosenOption;
	std::thread backend;
	static userInterface* singletonInstance;
	
	mediator eventHandler;

public:
	~userInterface();

	void showUserDialog();
	static userInterface* instance();
	mediator* shareEventHandler() {
		return &eventHandler;
	}
};

#endif // USERINTERFACE_H