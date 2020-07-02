#include "settings.h"

std::shared_ptr<settings> settings::instance{nullptr};

settings::settings(){
	parameter.profileName = "default";
}

std::shared_ptr<settings> settings::getInstance(){
	if(instance == nullptr){
		instance = std::make_shared<settings>(*(new settings()));
	}

	return instance;
}

settingsStruct settings::makeSnapshot(const std::string& _savedProfileName) {
	settingsStruct auxiliaryStruct = parameter;
	auxiliaryStruct.profileName = _savedProfileName;

	return auxiliaryStruct;
}