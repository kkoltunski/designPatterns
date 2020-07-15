#include "userInterface.h"

userInterface::userInterface(settings* _pToSettings) : pToSettings{ _pToSettings }, selector{ 0 }, choosenProfileNameIndex{ selector }{
	pToMemento = _pToSettings->shareMemento();
	optionsVector.push_back("Save");
	optionsVector.push_back("Load");
}

void userInterface::updateProfileList() {
	std::size_t mementoContainerSize = pToMemento->size();
	std::string profileName{};
	static int x{};

	profileName = pToMemento->getProfile(x);
	profileNames.push_back(profileName);
}

void userInterface::showProfileNamesContentInConsole() {
	std::size_t counter{ 0 };
	if (update) {
		updateProfileList();
		update = false;
	}

	if (!choosenProfileNameIndex) {
		system("CLS");


		for (auto iterator = std::begin(profileNames); iterator != std::end(profileNames); ++iterator, ++counter) {
			std::cout << (selector == counter ? ">" : " ") << (*iterator) << "\n";
		}
	}
}

void userInterface::showOptionsVectorInConsole() {
	std::size_t counter{ 0 };

	system("CLS");
	std::cout << std::endl;

	for (std::size_t counter = 0; counter < optionsVector.size(); ++counter) {
		std::cout << (selector == counter ? ">" : " ") << optionsVector[counter] << "\n";
	}
}

void userInterface::selectorValueControl() {
	int limit = (choosenProfileNameIndex || !profileNames.size()
					? optionsVector.size() : profileNames.size());

	if (selector >= limit) {
		selector = 0;
	}
	if (selector < 0) {
		selector = (limit - 1);
	}
}

void userInterface::getKey() {
	bool result{ true };

	do {
		switch (_getch()) {
		case KEY_UP:
			--selector;
			result = false;
			break;
		case KEY_DOWN:
			++selector;
			result = false;
			break;
		case KEY_ENTER:
			choosenProfileNameIndex = selector;
			selector = 0;
			result = 0;
			break;
		default:
			break;
		}
	} while (result);

	selectorValueControl();
}