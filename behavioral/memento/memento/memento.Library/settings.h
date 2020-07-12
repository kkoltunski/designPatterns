#ifndef SETTINGS_H
#define SETTINGS_H

#include <memory>
#include "settingsMemento.h"

class settings{
private:
	settingsStruct parameter;

	settingsMemento* memento;

protected:
	static std::shared_ptr<settings> instance;

	settings();

public:
	virtual ~settings() = default;
	static std::shared_ptr<settings> getInstance();
	settingsStruct makeSnapshot(const std::string& _savedProfileName = "");
	bool tryToSetSnapshot(const std::string& _profileName);
};

#endif // SETTINGS_H