#include "settingsMemento.h"

settingsMemento::settingsMemento(settings* _source) : source{ _source } {
};

bool settingsMemento::isUnique(const settingsStruct& _setToCheck) {
	bool unique = std::all_of(begin(settingsList), end(settingsList),
		[&](settingsStruct settings) {bool result{ false };
	if (settings.profileName != _setToCheck.profileName) { result = true; } return result; });

	return unique;
}

void settingsMemento::append(settings* _questionSource, const settingsStruct& _set) {
	if (_questionSource == source) {
		if (isUnique(_set)) {
			settingsList.push_back(_set);
		}
	}
}

settingsStruct settingsMemento::getProfile(settings* _questionSource, const std::string& _profileName) {
	if (_questionSource != source) {
		throw(std::exception("Question source is different than internal source."));
	}

	auto iterator = std::find_if(std::begin(settingsList), std::end(settingsList),
		[&](settingsStruct structure) {return (structure.profileName == _profileName); });

	if (iterator == std::end(settingsList)) { 
		throw(std::exception("Profile name not found."));
	}

	return *(iterator);
}

//This method shouldnt share whole settings struct it should only show partial informations
std::string settingsMemento::getProfile(std::size_t _index) {
	std::size_t counter{0};

	if (/*!settingsList.size() ||*/ (_index > settingsList.size() || _index < 0)) {
		throw(std::exception("Invalid index."));
	}
	
	if (settingsList.empty()) {
		throw(std::exception("Memento list is empty."));
	}

	auto iterator = std::find_if(std::begin(settingsList), std::end(settingsList),
		[&](settingsStruct settings)
		{bool result{ false }; if (counter++ == _index) { result = true; } return result; });

	return (*(iterator)).profileName;
}

std::size_t settingsMemento::size() {
	return settingsList.size();
}