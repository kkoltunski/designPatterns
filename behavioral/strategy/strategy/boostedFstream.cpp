#include "boostedFstream.h"

void boostedFstream::reopen(ios_base::openmode _newMode){
	close();
	open(filePath, _newMode);
	openedMode = _newMode;
}

void boostedFstream::loadFileContentToBuffer(){
	std::fstream::seekg(0, std::ios::end);
	unsigned long bufferLength = std::fstream::tellg();
	std::fstream::seekg(0, std::ios::beg);

	char* auxiliaryBuffer = new char[bufferLength];
	read(auxiliaryBuffer, bufferLength);
	
	buffer.str("");
	buffer.seekp(0, std::ios::beg);
	buffer.write(auxiliaryBuffer, bufferLength);

	delete[] auxiliaryBuffer;
}

void boostedFstream::loadBufferContentToFile(){
	char* auxiliaryBuffer = new char[buffer.str().size()];
	buffer.seekg(0, std::ios::beg);

	for(int i = 0; i < buffer.str().size(); i++, buffer.seekg(1, std::ios::cur)){
		auxiliaryBuffer[i] = buffer.peek();
	}

	write(auxiliaryBuffer, buffer.str().size());

	delete[] auxiliaryBuffer;
	buffer.str("");
}

void boostedFstream::changeOpenedMode(ios_base::openmode _newMode){
	try{
		if ((_newMode & (std::ios_base::trunc | std::ios_base::app)) == 24) {
			throw(std::exception("New openmode (std::ios_base::trunc with std::ios_base::app) is forbidden.\n"));
		}
		if(!is_open()){
			throw(std::exception("File is not opened.\n"));
		}
		
		_newMode |= std::ios::binary;

		if(openedMode != _newMode){
			bool truncation = (openedMode & _newMode) & std::ios_base::trunc;

			if(truncation){
				loadFileContentToBuffer();
				reopen(_newMode);
				loadBufferContentToFile();
			}
			else{
				reopen(_newMode);
			}

			//reopen(_newMode);
		}
	}
	catch(std::exception &exception){
		std::cout << exception.what() << std::endl;
	}
}

void boostedFstream::addOpenedMode(ios_base::openmode _modeToAdd){
	changeOpenedMode(openedMode | _modeToAdd);
}

std::string boostedFstream::getFileContent(){
	try{
		if(!(openedMode & std::ios::in)){
			throw(std::exception("Stream is not in std::ios::in mode.\n"));
		}

		std::string auxiliaryString = buffer.str();

		if (auxiliaryString.empty()) {
			loadFileContentToBuffer();
		}
	}
	catch(std::exception &exception){
		std::cout << exception.what() << std::endl;
		buffer.str("");
	}

	return buffer.str();
}

void boostedFstream::putContentToFile(const std::string& _newContent){
	try{
		if (!(openedMode & std::ios::out)) {
			throw(std::exception("Stream is not in std::ios::out mode.\n"));
		}

		std::ios_base::openmode previousOpenModeFlags = openedMode;

		buffer.str(_newContent);
		addOpenedMode(std::ios::trunc);
		loadBufferContentToFile();
		changeOpenedMode(previousOpenModeFlags);
	}
	catch (std::exception& exception) {
		std::cout << exception.what() << std::endl;
	}
}