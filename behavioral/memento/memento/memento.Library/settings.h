#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <memory>

struct settingsStruct{
	std::string profileName{};

};

class settings{
private:
	settingsStruct parameter;

protected:
	static std::shared_ptr<settings> instance;

	settings();

public:
	virtual ~settings() = default;
	static std::shared_ptr<settings> getInstance();
	settingsStruct makeSnapshot(const std::string& _savedProfileName);
};

#endif // SETTINGS_H