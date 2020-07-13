#include "settings.h"

std::shared_ptr<settings> settings::instance{nullptr};

settings::settings(){
	parameters.profileName = "default";
}

std::shared_ptr<settings> settings::getInstance(){
	if(instance == nullptr){
		instance = std::make_shared<settings>(*(new settings()));
		instance->memento = new settingsMemento(instance.get());
	}

	return instance;
}

settingsStruct settings::makeSnapshot(const std::string& _savedProfileName) {
	settingsStruct auxiliaryStruct = parameters;

	if (!_savedProfileName.empty()) {
		auxiliaryStruct.profileName = _savedProfileName;
	}

	memento->append(this, auxiliaryStruct);

	return auxiliaryStruct;
}

bool settings::tryToSetSnapshot(const std::string& _profileName) {
	bool result{false};

	try {
		parameters = memento->getProfile(this, _profileName);
		result = true;
	}
	catch (std::exception& exception) {
		std::cout << exception.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unhandled exception." << std::endl;
	}

	return result;
}