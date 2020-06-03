#ifndef FRAMES_H
#define FRAMES_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include "structures.h"
#include "errodHandling.h"

extern std::ostream& operator<<(std::ostream& _ostream, uartByte& _uByte);

enum constValues : short { minDataSize = 4, maxDataSize = 246, minProfibusAddress = 0, maxProfibusDestinationAddress = 127, 
					maxProfibusSourceAddress = 126,
};
enum class frameConstants : short {sd1 = 0x10 , sd2 = 0x68, sd3 = 0xA2, sd4 = 0xDC, ed = 0x16, sc = 0xE5};
enum class functionCodeRanges : int {lowerRange = 0x0, requestMaxRange = 0xF, responseMaxRange = 0xD};

class profibusDPFrameWithVariableData{
private:
	bool isNewDataValid(const std::string& _toValidation);

protected:
	virtual void fillConstants();
	virtual uint8_t setDestinationAddressAndReturnValue() = 0;
	virtual uint8_t generateRandomFunctionCodeAndReturnValue() = 0;
	virtual void putDataFieldIntoFrame();
	virtual void putFrameCheckSumIntoFrame(uint8_t _addresses, uint8_t _functionCode);
	virtual void finishFrame();

	std::stringstream buffer{ "" };
	std::string data{ "    " };

public:
	virtual void generate();
	void setNewData(const std::string& _newData);
};

class sd2RequestFrame : public profibusDPFrameWithVariableData {
private:
	uint8_t getDestinationAdress();

protected:
	virtual uint8_t setDestinationAddressAndReturnValue() override;
	virtual uint8_t generateRandomFunctionCodeAndReturnValue() override;

	char deviceAddress;

public:
	sd2RequestFrame(char _deviceAddress) : deviceAddress{ _deviceAddress }{
	}
};

class sd2ResponseFrame : public profibusDPFrameWithVariableData {
private:
	uint8_t getSourceAddress();

protected:
	virtual uint8_t setDestinationAddressAndReturnValue() override;
	virtual uint8_t generateRandomFunctionCodeAndReturnValue() override;

	short deviceAddress;

public:
	sd2ResponseFrame(char _deviceAddress) : deviceAddress{ _deviceAddress } {
	}
};

#endif // FRAMES_H