#include "mp3FileAdapter.h"

void mp3FileAdapter::formatValidation(){
	unsigned long long int readedSignature = file.readSignature(signatureLength::mp3SignatureBytesLength);

	if (readedSignature == static_cast<unsigned long long int>(file.formatSignature)) {
		std::cout << "MP3 file signature valid." << std::endl;
	}
	else {
		std::cout << "MP3 file signature not valid." << std::endl;
	}
}