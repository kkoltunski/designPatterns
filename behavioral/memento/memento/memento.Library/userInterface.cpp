#include "userInterface.h"

userInterface::userInterface(settings* _pToSettings) 
	: pToSettings{ _pToSettings }, optionSelector{ 0 }, profileNameIndex{ optionSelector }, actualControl{optionControl}{
	pToMemento = _pToSettings->shareMemento();
	optionsVector.push_back("Save");
	optionsVector.push_back("Load");
}

void userInterface::updateProfileList() {
	std::size_t mementoContainerSize = pToMemento->size();
	std::size_t sizeDifference = (mementoContainerSize - profileNames.size());
	std::string profileName{};

	for (std::size_t i = profileNames.size(); i < sizeDifference; ++i) {
		profileName = pToMemento->getProfile(i);
		profileNames.push_back(profileName);
	}
}

void userInterface::showProfileNamesContentInConsole() {
	std::size_t counter{ 0 };

	updateProfileList();

	std::cout << "Available profiles to load: " << std::endl;

	for (auto iterator = std::begin(profileNames); iterator != std::end(profileNames); ++iterator, ++counter) {
		std::cout << (profileNameIndex == counter ? ">" : " ") << (*iterator) << "\n";
	}
	std::cout << "\n"; 
}

void userInterface::showOptionsVectorInConsole() {
	std::size_t counter{ 0 };
	
	std::cout << "Choose option you want to do: " << std::endl;

	for (std::size_t counter = 0; counter < optionsVector.size(); ++counter) {
		std::cout << (optionSelector == counter ? ">" : " ") << optionsVector[counter] << "\n";
	}
}

void userInterface::selectorValueControl() {
	limit<int> optionSelectorLimit{0, static_cast<int>(optionsVector.size() - 1) };
	limit<int> profileIndexLimit{0, static_cast<int>(profileNames.size() - 1) };

	optionSelectorLimit.adjustIfDoesnttMatch(optionSelector);
	profileIndexLimit.adjustIfDoesnttMatch(profileNameIndex);
}

void userInterface::keyFilter() {
	bool result{ true };

	do {
		switch (pressedKey = _getch()) {
		case KEY_UP:
			--(actualControl ? profileNameIndex : optionSelector);
			result = false;
			break;
		case KEY_DOWN:
			++(actualControl ? profileNameIndex : optionSelector);
			result = false;
			break;
		case KEY_ENTER:
			actualControl = (!actualControl && optionSelector ? profileControl : optionControl);
			result = false;
			break;
		default:
			break;
		}
	} while (result);

	selectorValueControl();
}

void userInterface::actionPerformance() {
	if (actualControl) {
		showProfileNamesContentInConsole();
		if (pressedKey == KEY_ENTER) {
			loadOrder();
		}
	}
	else {
		if (pressedKey == KEY_ENTER && !optionSelector) {
			saveOrder();
		}
	}
}

void userInterface::loadOrder() {
	try {
		const std::string auxiliaryProfileName = pToMemento->getProfile(profileNameIndex);
		pToSettings->tryToSetSnapshot(auxiliaryProfileName);
	}
	catch (std::exception& exception) {
		std::cout << exception.what() << std::endl;
		actualControl = optionControl;
	}
}

std::string userInterface::getUserType() {
	bool streamError{ false };
	std::string savedProfileName{};

	do {
		system("CLS");
		std::cout << "Type new profile name: ";
		getline(std::cin, savedProfileName);

		if (std::cin.fail()) {
			streamError = true;
		}
		std::cin.clear();
	} while (streamError);

	return savedProfileName;
}

void userInterface::saveOrder() {
	std::string newProfileName{ getUserType() };
	pToSettings->makeSnapshot(newProfileName);
}