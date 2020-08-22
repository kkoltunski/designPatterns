#include "userInterface.h"

userInterface* userInterface::singletonInstance{ nullptr };

userInterface::userInterface() : m_currentlyPointed{}, m_choosenOption{std::rand()}, m_currentlyPointedChange{ true }{
	backend = std::thread([this] {backendLoop(); });
}

userInterface::~userInterface(){
	if (backend.joinable()) {
		backend.join();
	}
}

userInterface* userInterface::instance() {
	if (!singletonInstance) {
		singletonInstance = new userInterface;
	}

	return singletonInstance;
}

void userInterface::backendLoop() {
	m_currentlyPointed = 0;
	
	do {
		char keyPressed = _getch();

		uglySwitch(keyPressed);
	} while (true);
}

void userInterface::showUserDialog() {
	if (m_currentlyPointedChange) {
		system("cls");
		std::cout << "Choose option using arrows and pressing enter." << std::endl;
		for (size_t i = 0; i < POSSIBLE_EVENTS; ++i) {
			std::cout << (m_currentlyPointed == i ? ">" : " ")
				<< eventsNames[i] << " event." << std::endl;
		}

		m_currentlyPointedChange = false;
	}
}

void userInterface::choosenOptionChange() {
	eventHandler.reloadActiveEvent(m_choosenOption);
}

void userInterface::currentlyPointedControl() {
	auto absolutePossibleEvents = POSSIBLE_EVENTS - 1;

	if (m_currentlyPointed > absolutePossibleEvents) {
		m_currentlyPointed = 0;
	}
	else if(m_currentlyPointed < 0) {
		m_currentlyPointed = absolutePossibleEvents;
	}
}

void userInterface::uglySwitch(int _option) {
	switch (_option) {
	case KEY_UP:
		--m_currentlyPointed;
		m_currentlyPointedChange = true;
		break;
	case KEY_DOWN:
		++m_currentlyPointed;
		m_currentlyPointedChange = true;
		break;
	case KEY_ENTER:
		if (m_choosenOption != m_currentlyPointed) {
			m_choosenOption = m_currentlyPointed;
			choosenOptionChange();
		}
		break;
	}
	currentlyPointedControl();
}