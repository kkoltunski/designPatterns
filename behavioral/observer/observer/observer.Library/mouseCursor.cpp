#include "mouseCursor.h"

bool mouseCursor::setStateIfDifferent(POINT _position) {
	bool result{ false };

	if ((_position.x != position.x) || (_position.y != position.y)) {
		position.x = _position.x;
		position.y = _position.y;

		notify();

		result = true;
	}	

	return result;
}

void mouseCursor::notify() {
	std::cout << "CHANGE! x = " << position.x << ", y = " << position.y << std::endl;
	std::for_each(std::begin(observersList), std::end(observersList), [&](observer* _observer) {_observer->update(this); });
}
