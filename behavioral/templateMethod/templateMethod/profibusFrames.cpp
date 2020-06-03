#include "profibusFrames.h"

void profibusDPFrameWithVariableData::fillConstants() {
	uartByte sd2{ static_cast<char>(frameConstants::sd2) };
	buffer << "|" << sd2 << "|" << data.size() << "|" << data.size() << "|" << sd2;
}

void profibusDPFrameWithVariableData::putDataFieldIntoFrame() {
	buffer << "|" << data;
}

void profibusDPFrameWithVariableData::putFrameCheckSumIntoFrame(uint8_t _addresses, uint8_t _functionCode){
	uint8_t dataSize = static_cast<uint8_t>(data.size());
	uint8_t FCS =_addresses | _functionCode;
	FCS |= dataSize;

	buffer << "|" << FCS;
}

void profibusDPFrameWithVariableData::finishFrame(){
	uartByte ed(static_cast<char>(frameConstants::ed));
	buffer << "|" << ed << "|";
	std::cout << buffer.str() << std::endl;
}

bool profibusDPFrameWithVariableData::isNewDataValid(const std::string& _toValidation) {
	return ((_toValidation.size() >= minDataSize) && (_toValidation.size() <= maxDataSize));
}

void profibusDPFrameWithVariableData::setNewData(const std::string& _newData) {
	try {
		if (data == "    ") {
			if (isNewDataValid(_newData)) {
				data = _newData;
			}
			else {
				throw(wrongData("Data is too short or too long."));
			}
		}
		else {
			throw(std::exception("Data field is occupied."));
		}
	}
	catch (wrongData& exception) {
		std::cout << exception.what() << " Data will be filled by default field.\n" << std::endl;
		data = "    ";
	}
	catch (std::exception& exception) {
		std::cout << exception.what();
	}
}

void profibusDPFrameWithVariableData::generate(){
	uint8_t DASA{}, FC{};

	fillConstants();
	DASA = setDestinationAddressAndReturnValue();
	FC = generateRandomFunctionCodeAndReturnValue();
	putDataFieldIntoFrame();
	putFrameCheckSumIntoFrame(DASA, FC);
	finishFrame();
}

uint8_t sd2RequestFrame::getDestinationAdress(){
	int destinationAddress{ 0 };
	bool streamStateFail{ false };

	do{
		std::cout << "Type address in range from 0 to 127 : " << std::endl;

		std::cin >> destinationAddress;
		streamStateFail = std::cin.fail();

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (streamStateFail || ((destinationAddress < minProfibusAddress) || destinationAddress > maxProfibusDestinationAddress));
	
	return destinationAddress;
}

uint8_t sd2RequestFrame::setDestinationAddressAndReturnValue(){
	short destinationAddress = getDestinationAdress();
	
	buffer << "|" << destinationAddress << false << "|" << deviceAddress << false;

	return destinationAddress | deviceAddress;
}

uint8_t sd2RequestFrame::generateRandomFunctionCodeAndReturnValue() {
	std::random_device random; // obtain a random number from hardware
	std::mt19937 eng(random()); // seed the generator
	std::uniform_int_distribution<> 
		distr(static_cast<int>(functionCodeRanges::lowerRange), static_cast<int>(functionCodeRanges::requestMaxRange)); // define the range
	auto FC = distr(eng);

	buffer << "|" << FC;

	return FC;
}

uint8_t sd2ResponseFrame::getSourceAddress() {
	int sourceAddress{ 0 };
	bool streamStateFail{ false };

	do {
		std::cout << "Type address in range from 0 to 126 : " << std::endl;

		std::cin >> sourceAddress;
		streamStateFail = std::cin.fail();

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (streamStateFail || ((sourceAddress < minProfibusAddress) || sourceAddress > maxProfibusSourceAddress));

	return sourceAddress;
}

uint8_t sd2ResponseFrame::setDestinationAddressAndReturnValue() {
	uint8_t destinationAddress = getSourceAddress();

	buffer << "|" << deviceAddress << false << "|" << destinationAddress << false;
	std::cout << "destinationAddress = " << (int)destinationAddress << std::endl;
	std::cout << "deviceAddress = " << (int)deviceAddress << std::endl;

	return destinationAddress | deviceAddress;
}

uint8_t sd2ResponseFrame::generateRandomFunctionCodeAndReturnValue() {
	std::random_device random; // obtain a random number from hardware
	std::mt19937 eng(random()); // seed the generator
	std::uniform_int_distribution<> 
		distr(static_cast<int>(functionCodeRanges::lowerRange), static_cast<int>(functionCodeRanges::responseMaxRange)); // define the range
	auto FC = distr(eng);

	buffer << "|" << FC;

	return FC;
}