#include "formats.h"

flacFile::flacFile(const std::string &_pathToFile) : file(_pathToFile) {
	file.setSignature(signature::flacSignature);

	file.openFile();
	formatValidation();
}

void flacFile::formatValidation(){
	unsigned long long int readedSignature = file.readSignature(signatureLength::flacSignatureBytesLength);
	
	if(readedSignature == static_cast<unsigned long long int>(file.formatSignature)){
		std::cout << "FLAC file signature valid." << std::endl;
	}
	else{
		std::cout << "FLAC file signature not valid." << std::endl;
	}
}

mp3File::mp3File(const std::string &_pathToFile) : file(_pathToFile) {
	file.openFile();
}