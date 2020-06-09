#ifndef BOOSTEDFSTREAM_H
#define BOOSTEDFSTREAM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class boostedFstream : public std::fstream{
protected:
	void reopen(ios_base::openmode mode);
	void loadFileContentToBuffer();
	void loadBufferContentToFile();

	const std::string filePath;
	ios_base::openmode openedMode;

	std::stringstream buffer;

public:
	boostedFstream(const char* filename, ios_base::openmode mode = ios_base::in | ios_base::out)
		: std::fstream(filename, (mode | ios_base::binary)), filePath( filename ), openedMode{ (mode | ios_base::binary) }, buffer(""){
	}
	boostedFstream(const std::string& filename, ios_base::openmode mode = ios_base::in | ios_base::out)
		: std::fstream(filename, (mode | ios_base::binary)), filePath(filename), openedMode{ (mode | ios_base::binary) }, buffer(""){
	}
	void changeOpenedMode(ios_base::openmode _newMode);
	void addOpenedMode(ios_base::openmode _modeToAdd);
	std::string getFileContent();
	void putContentToFile(const std::string& _newContent);
};

#endif // BOOSTEDFSTREAM_H