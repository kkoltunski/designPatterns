#ifndef HEADER_H
#define HEADER_H

#include <thread>
#include "profibusFrames.h"

std::ostream& operator<<(std::ostream& _ostream, uartByte& _uByte) {
	_ostream << _uByte.stopBit << _uByte.parityBit << static_cast<char>(_uByte.infoBits) << _uByte.startBit;
	return _ostream;
}

#endif // HEADER_H