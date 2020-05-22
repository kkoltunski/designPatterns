#include "importantFile.h"

programConfigFile* programConfigFile::instance{ nullptr };

file::file(const std::string& _filePath) {
	fileStream.path = _filePath;
}

bool file::isStreamOpen() const{
	bool result{ true };

	try{
		if (!fileStream.stream.is_open()){
			result = false;
			std::string message = "Stream to " + fileStream.path + " is not opened.\n";
			throw(std::exception(message.c_str()));
		}
	}
	catch (std::exception& expection) {
		std::cout << expection.what() << std::endl;
	}

	return result;
}

bool file::isStreamGood() const{
	bool result{ true };

	try {
		if (fileStream.stream.fail()) {
			result = false;
			std::string message = "Stream to " + fileStream.path + " is broken.\n";
			throw(std::exception(message.c_str()));
		}
	}
	catch (std::exception& expection) {
		std::cout << expection.what() << std::endl;
	}

	return result;
}

std::streamsize file::getFileSize() const{
	std::streamsize result{ 0 };
	std::streamsize positionMemory = fileStream.stream.tellg();

	fileStream.stream.seekg(0, std::ios_base::end);
	result = fileStream.stream.tellg();

	fileStream.stream.seekg(positionMemory, std::ios_base::beg);

	return result;
}

void settingsFile::saveParameter(std::streampos _beginingByte, std::size_t _byteLength){
	parameterData auxiliaryParameter;

	auxiliaryParameter.byteInFile = _beginingByte;
	auxiliaryParameter.length = _byteLength;
	parameters.push_back(auxiliaryParameter);
}

void settingsFile::makeFile(const char* _settingsArgument[]) {
	if (isStreamOpen() && isStreamGood()) {
		makeIntro();
		writeSettings(_settingsArgument);
	}
}

programConfigFile::programConfigFile(int _settingsArgumentNumber, const char* _settingsArgument[]) 
	: settingsFile(_settingsArgumentNumber, _settingsArgument) 
{
	fileStream.stream.open(fileStream.path, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
	makeFile(_settingsArgument);
}

void programConfigFile::makeIntro(){
	fileStream.stream << "This is PROXY design pattern program implementation.\r\n\r\nSettings\r\n";
}

void programConfigFile::createInstance(int _settingsArgumentNumber, const char* _settingsArgument[]){
	try{
		if (instance == nullptr) {
			instance = new programConfigFile(_settingsArgumentNumber, _settingsArgument);
		}
		else{
			throw(std::exception("Instance already exist. Try to use getInstance().\n"));
		}
	}
	catch(std::bad_alloc &exception){
		std::cout << exception.what() << std::endl;
		terminate();
	}
	catch(std::exception &exception){
		std::cout << exception.what() << std::endl;
	}
}

void programConfigFile::writeSettings(const char* _settingsArgument[]){
	if (isStreamOpen() && isStreamGood()) {
		for(int i = 0; i < argumentNumber; ++i){
			fileStream.stream << "\t{~option" << i << " := ";
			saveParameter(fileStream.stream.tellg(), strlen(_settingsArgument[i]));
			fileStream.stream << _settingsArgument[i] << "};\r\n";
		}

		fileStream.stream.clear();
	}
}

std::list<parameterData>::const_iterator programConfigFile::findIterator(int _index) const {
	auto auxiliaryIterator = parameters.begin();

	for (int i = 0; i < _index; ++i) {
		++auxiliaryIterator;
	}

	return auxiliaryIterator;
}

bool programConfigFile::isIndexCorrect(int _indexParameter) const{
	bool result{ true };
	int absoluteParametersSize = (parameters.size() - 1);

	try{
		if ((_indexParameter > absoluteParametersSize) || (_indexParameter < 0)){
			result = false;
			std::string message = "Index number [" + std::to_string(_indexParameter) + "] overloaded.\n";
			throw(std::exception(message.c_str()));
		}
	}
	catch(std::exception &exception){
		std::cout << exception.what() << std::endl;
	}

	return result;
}

std::shared_ptr<std::string> programConfigFile::makeFileBuffer() const{
	std::shared_ptr<std::string> pToBuffer{nullptr};
	std::streamsize fileSizeInBytes = getFileSize();
	char* fileContent = new char[static_cast<unsigned int>(fileSizeInBytes)];

	fileStream.stream.seekg(0, std::ios_base::beg);
	fileStream.stream.read(fileContent, getFileSize());
	pToBuffer = std::make_shared<std::string>(std::string(fileContent));

	delete [] fileContent;
	return pToBuffer;
}

void programConfigFile::writeParameter(std::string _value, int _indexParameter) const{
	if (isStreamOpen() && isStreamGood() && isIndexCorrect(_indexParameter)) {
		auto parameterIterator = findIterator(_indexParameter);
		std::shared_ptr<std::string> pToBuffer = makeFileBuffer();

		pToBuffer->erase(static_cast<unsigned int>(parameterIterator->byteInFile), parameterIterator->length);
		pToBuffer->insert(static_cast<unsigned int>(parameterIterator->byteInFile), _value);
		pToBuffer->erase((pToBuffer->rfind(';') + 1));								//cleaning last 8 bytes (i dont know why it is trash)

		fileStream.stream.close();
		fileStream.stream.open(fileStream.path, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);

		fileStream.stream << *pToBuffer;

		fileStream.stream.clear();
	}
}

void programConfigFile::readParameter(int _indexParameter) const {
	if (isStreamOpen() && isStreamGood() && isIndexCorrect(_indexParameter)) {
		auto parameterIterator = findIterator(_indexParameter);
		std::string parameterValue;

		fileStream.stream.seekg(parameterIterator->byteInFile, std::ios_base::beg);
		std::getline(fileStream.stream, parameterValue, '}');
		std::cout << "Parameter" << _indexParameter << " = " << parameterValue << std::endl;

		fileStream.stream.clear();
	}
}

std::string programConfigFileProtectionProxy::getUserTypedPassword() const {
	std::string typedPassword{ "" };

	std::cout << "Type password to file : ";
	std::getline(std::cin, typedPassword);

	return typedPassword;
}

bool programConfigFileProtectionProxy::isPasswordCorrect(std::string _userTypedPassword) const {
	bool result{ true };

	if(_userTypedPassword != accessPassword){
		std::cout << "Typed password to file is incorrect\n";
		result = false;
	}

	return result;
}

void programConfigFileProtectionProxy::writeParameter(std::string _value, int _indexParameter) const {
	if (isPasswordCorrect(getUserTypedPassword())) {
		_file.writeParameter(_value, _indexParameter);
	}
}

void programConfigFileProtectionProxy::readParameter(int _indexParameter) const {
	if (isPasswordCorrect(getUserTypedPassword())) {
		_file.readParameter(_indexParameter);
	}
}