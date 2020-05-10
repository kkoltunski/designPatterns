#include "interfaces.h"

template<typename T>
void littleToBig(T &_toConvert){
	T storage{ 0 };

	if(sizeof(T) > 1){
		for(short i = sizeof(T); i > 0; i--){
			storage <<= 8;
			storage += (_toConvert & 0xFF);
			_toConvert >>= 8;
		}

		_toConvert = storage;
	}

}

void iFileStream::openFile() {
	try {
		stream.open(path, std::ifstream::binary);

		if (!stream.is_open()) {
			throw(openingFileFail(path));
		}
	}
	catch (openingFileFail &exception) {
		std::cout << exception.what() << std::endl;
		terminate();
	}
}

unsigned long long int iFileStream::readSignature(signatureLength _signatureLength, int _signatureFirstBytePosition){
	unsigned long long int result{ 0 };

	try{
		if (stream.is_open()) {
			if(!stream.fail()){
				stream.seekg(_signatureFirstBytePosition, std::ios::beg);
				stream.read((char*)&result, static_cast<std::streamsize>(_signatureLength));
				littleToBig(result);
			}
			else{
				throw(streamIsBroken());
			}
		}
		else{
			throw(openingFileFail(path));
		}
	}
	catch(openingFileFail &exception){
		std::cout << exception.what() << std::endl;
		terminate();
	}
	catch(streamIsBroken &exception){
		std::cout << exception.what() << std::endl;
		terminate();
	}

	return result;
}