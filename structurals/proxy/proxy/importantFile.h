#ifndef IMPORTANDFILE_H
#define IMPORTANDFILE_H

#include <list>
#include <vector>
#include <sstream>
#include <memory>
#include "structures.h"

class file{
protected:
	mutable stream fileStream;

public:
	 file(const std::string &_filePath);
	bool isStreamOpen() const;
	bool isStreamGood() const;
	std::streamsize getFileSize() const;
	virtual void writeParameter(std::string _value, int _indexParameter) const = 0;
	virtual void readParameter(int _indexParameter) const = 0;						//Sometimes different settings file have various formats
};

class settingsFile : public file{
protected:
	void makeFile(const char* _settingsArgument[]);
	virtual void makeIntro() = 0;
	virtual void writeSettings(const char* _settingsArgument[]) = 0;				//Sometimes different settings file have various formats
	void saveParameter(std::streampos _beginingByte, std::size_t _byteLength);
	std::list<parameterData> parameters;
	int argumentNumber;

public:
	settingsFile(int _settingsArgumentNumber, const char* _settingsArgument[]) : file(_settingsArgument[1]), argumentNumber{ _settingsArgumentNumber }{
	}
};

class programConfigFile : public settingsFile {
private:
	virtual void makeIntro() override;
	virtual void writeSettings(const char* _settingsArgument[]) override;
	std::list<parameterData>::const_iterator findIterator(int _index) const ;
	bool isIndexCorrect(int _index) const;
	std::shared_ptr<std::string> makeFileBuffer() const;

protected:
	programConfigFile(int _settingsArgumentNumber, const char* _settingsArgument[]);

	static programConfigFile *instance;

public:
	static void createInstance(int _settingsArgumentNumber, const char* _settingsArgument[]);
	static inline const programConfigFile& getInstance(){
		return *instance;
	}
	virtual void writeParameter(std::string _value, int _indexParameter) const override;
	virtual void readParameter(int _indexParameter) const override;
};

//Proxy - similar to decorator
class programConfigFileProtectionProxy : public file {
private:
	std::string getUserTypedPassword() const;
	bool isPasswordCorrect(std::string) const;
	const file &_file;
	const std::string accessPassword{ "proxyguard" };

public:
	programConfigFileProtectionProxy(const programConfigFile& _referenceToConfigFile) : file("Proxyguard"), _file{ _referenceToConfigFile } {
	};
	virtual void writeParameter(std::string _value, int _indexParameter) const override;
	virtual void readParameter(int _indexParameter) const override;
};
#endif // IMPORTANDFILE_H