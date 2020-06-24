#ifndef DIRECTORYMANAGEMENT_H
#define DIRECTORYMANAGEMENT_H

//necessary to use ::max()
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <functional>
#include <algorithm>

//#undef max
//#undef min

class iFile{
protected:
	std::string extractFileName();

	std::string filePath;
	bool exist;

public:
	explicit iFile(const LPCSTR& _filePath);
	virtual bool tryToCreate() = 0;
	virtual bool tryToRemove() = 0;
	bool isFileExisting(DWORD _attributesToCheck);
	bool isFileExisting();
	bool isFileNameEqual(const std::string& _fileName);
};

class file final : public iFile {
private:
	std::ios::openmode openMode;
	std::fstream fileStream;

public:
	file(const LPCSTR& _filePath, std::ios::openmode _openMode = std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
	virtual bool tryToCreate() override;
	virtual bool tryToRemove() override;
};

class directory final : public iFile {
private:
	bool tryToCleanDirectory();
	bool tryToPushBack(iFile* _addressToPushBack, DWORD _attributesToCheck);

	LPSECURITY_ATTRIBUTES directoryAtributes;
	std::list<iFile*> filesCollection;

public:
	directory(const LPCSTR& _newDirectoryPath, const LPSECURITY_ATTRIBUTES& _atributes = nullptr);
	virtual bool tryToCreate() override;
	virtual bool tryToRemove() override;
	iFile* tryToAddFileToDirectory(const std::string& _fileName, std::ios::openmode _openMode = std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
	iFile* tryToAddFolderToDirectory(const std::string& _fileName, const LPSECURITY_ATTRIBUTES& _atributes = nullptr);
	iFile* searchForFile(const std::string& _fileName);
};

#endif // DIRECTORYMANAGEMENT_H