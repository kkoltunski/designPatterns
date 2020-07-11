#ifndef SETTINGSMEMENTO_H
#define SETTINGSMEMENTO_H

#include <string>
#include <list>
#include <algorithm>
#include <iostream>

class settings;

struct settingsStruct {
	std::string profileName{};

};

class settingsMemento{
private:
	bool isUnique(const settingsStruct& _setToCheck);
	std::list<settingsStruct> settingsList;

	settings* source;

public:
	settingsMemento(settings* _source);
	void append(settings* _questionSource, const settingsStruct& _set);
	settingsStruct getProfile(settings* _questionSource, const std::string& _profileName);
	std::size_t size();
};

#endif // SETTINGSMEMENTO_H