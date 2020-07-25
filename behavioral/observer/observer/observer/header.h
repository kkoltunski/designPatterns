#ifndef HEADER_H
#define HEADER_H

#include <thread>
#include "screenField.h"

void mouseCursorPositionGetter(mouseCursor* _mouse) {
	POINT position{};

	do {
		GetCursorPos(&position);
		_mouse->setStateIfDifferent(position);
	} while (true);
}

#endif // HEADER_H
