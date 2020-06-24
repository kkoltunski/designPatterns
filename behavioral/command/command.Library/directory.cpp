#include "directory.h"

//file interface methods
iFile::iFile(const LPCSTR& _filePath) : filePath{ static_cast<std::string>(_filePath) }, exist{false}{
}

bool iFile::isFileExisting(DWORD _attributesToCheck) {
	bool result{ true };
	DWORD fileAtributes = GetFileAttributesA(filePath.c_str());

	if ((fileAtributes == INVALID_FILE_ATTRIBUTES) || !(fileAtributes & _attributesToCheck)) {
		result = false;
	}
	
	return result;
}

bool iFile::isFileExisting() {
	return exist;
}

std::string iFile::extractFileName() {
	std::size_t namePositionInPath = filePath.rfind('\\');
	std::string extractedName = filePath.substr(namePositionInPath + 1, std::string::npos);

	return extractedName;
}

bool iFile::isFileNameEqual(const std::string& _fileName){
	std::string extractedNameFromPath{ extractFileName() };

	return (extractedNameFromPath == _fileName ? true : false);
}

//file methods
file::file(const LPCSTR& _filePath, std::ios::openmode _openMode) : iFile(_filePath), openMode{ _openMode } {
	exist = isFileExisting(FILE_ATTRIBUTE_ARCHIVE);
}

bool file::tryToCreate(){
	bool result{ false };

	fileStream.open(filePath, openMode);
	
	if(isFileExisting(FILE_ATTRIBUTE_ARCHIVE)){
		exist = result = true;
	}

	return result;
}

bool file::tryToRemove() {
	bool result{false};

	if(exist){
		fileStream.close();
		if (DeleteFileA(filePath.c_str())) {
			exist = false;
			result = true;
		}
	}
	return result;
}

//directory methods
directory::directory(const LPCSTR& _newDirectoryPath, const LPSECURITY_ATTRIBUTES& _atributes)
	: iFile(_newDirectoryPath), directoryAtributes{ _atributes }
{
	exist = isFileExisting(FILE_ATTRIBUTE_DIRECTORY);
}

bool directory::tryToCreate() {
	bool result{ true };

	if(!exist){
		result = CreateDirectoryA(static_cast<LPCSTR>(filePath.c_str()), directoryAtributes);
		exist = result;
	}

	return result;
}

bool directory::tryToRemove(){
	bool result{ false };

	if(exist){
		if(tryToCleanDirectory()){
			if (RemoveDirectoryA(filePath.c_str())) {
				exist = false;
				result = true;
			}
		}
	}

	return result;
}

iFile* directory::tryToAddFileToDirectory(const std::string& _fileName, std::ios::openmode _openMode){
	std::string newFilePath{ filePath + "\\" + _fileName };
	file* result{ nullptr };
	file* pToNewFile{ new file(static_cast<LPCSTR>(newFilePath.c_str()), _openMode) };
	bool isAdded{ false };

	pToNewFile->tryToCreate();
	isAdded = tryToPushBack(pToNewFile, FILE_ATTRIBUTE_ARCHIVE);

	if(isAdded){
		result = pToNewFile;
	}

	return result;
}

iFile* directory::tryToAddFolderToDirectory(const std::string& _fileName, const LPSECURITY_ATTRIBUTES& _atributes){
	std::string newFolderPath{ filePath + "\\" + _fileName };
	directory* result{ nullptr };
	directory* pToNewFolder{ new directory(static_cast<LPCSTR>(newFolderPath.c_str()), _atributes) };
	bool isAdded{ false };

	pToNewFolder->tryToCreate();
	isAdded = tryToPushBack(pToNewFolder, FILE_ATTRIBUTE_DIRECTORY);

	if(isAdded){
		result = pToNewFolder;
	}

	return result;
}

bool directory::tryToCleanDirectory(){
	bool result{ false };
	std::function<bool(iFile*)> isFileRemovable = [&](iFile* pToFile)
	{bool lambdaResult{ true }; if (pToFile->isFileExisting()) { lambdaResult = pToFile->tryToRemove(); } return lambdaResult;};

	result = std::all_of (std::begin(filesCollection), std::end(filesCollection), isFileRemovable);

	return result;
}

bool directory::tryToPushBack(iFile* _addressToPushBack, DWORD _attributesToCheck){
	bool result{ false };

	if (_addressToPushBack->isFileExisting(_attributesToCheck)) {
		filesCollection.push_back(_addressToPushBack);
		result = true;
	}
	else {
		delete _addressToPushBack;
	}

	return result;
}

iFile* directory::searchForFile(const std::string& _fileName){
	std::function<bool(iFile*)> fileNameChecking = [&](iFile* pToObject)
	{bool lambdaResult{ false }; if (pToObject->isFileExisting()) {if (pToObject->isFileNameEqual(_fileName)) { lambdaResult = true;} } return lambdaResult;	};
	iFile* pToFile{ nullptr };

	auto pToObject = std::find_if(std::begin(filesCollection), std::end(filesCollection), fileNameChecking);

	if(pToObject != filesCollection.end()){
		pToFile = (*pToObject);
	}

	return pToFile;
}
