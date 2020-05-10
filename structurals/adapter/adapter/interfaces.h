#ifndef INTERFACES_H
#define INTERFACES_H

#include <string>
#include <iostream>
#include <fstream>
#include "errorHandling.h"

enum class signature : unsigned long long int{ flacSignature = 7371373630489362466, mp3Signature = 4801587};
enum class signatureLength : short { flacSignatureBytesLength = 8, mp3SignatureBytesLength = 3 };

struct iFormatValidator{
protected:
	virtual void formatValidation() = 0;
};

struct iSignatureManagement{
public:
	void setSignature(signature _signature){
		formatSignature = _signature;
	}
	virtual unsigned long long int readSignature(signatureLength _signatureLength, int _signatureFirstBytePosition = 0) = 0;

	signature formatSignature;
};

class iFileStream : public iSignatureManagement {
protected:
	std::string path;
	std::ifstream stream;

public:
	iFileStream(std::string _filePath) : path{ _filePath }{
	}
	void openFile();
	virtual unsigned long long int readSignature(signatureLength _signatureLength, int _signatureFirstBytePosition = 0) override;
};

#endif // INTERFACES_H
