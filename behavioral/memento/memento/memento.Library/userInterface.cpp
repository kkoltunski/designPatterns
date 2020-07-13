#include "userInterface.h"

userInterface::userInterface(settings* _pToSettings) : pToSettings{ _pToSettings } {
	pToMemento = _pToSettings->shareMemento();
}

void userInterface::showOptions() {
	std::string profileName{};
	std::size_t selectedOption{};
	std::size_t mementoContainerSize = pToMemento->size();

	system("CLS");

	for (std::size_t x = 0; x < mementoContainerSize; ++x) {
		profileName = pToMemento->getProfile(x);

		if (selectedOption == x) {
			std::cout << ">";
		}
		else {
			std::cout << " ";
		}

		std::cout << profileName << "\n";
	}
}