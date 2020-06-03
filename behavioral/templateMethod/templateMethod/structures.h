#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <bitset>

//LSB->MSB dir
struct uartByte {
public:
	unsigned short startBit : 1,
			infoBits : 8,
			parityBit : 1,
			stopBit : 1;

	uartByte(uint8_t _infoVal, bool _parity = false) : startBit{ false }, infoBits(_infoVal), parityBit{ _parity }, stopBit{true}{
	}
};

#endif // STRUCTURES_H
