#include "header.h"

int main() {
	mouseCursor* pToMouseCursor = new mouseCursor();



	screenField* pToTopLeftCorner = new screenField(coordinates(0,0), 100);
	screenField* pToTopRightCorner = new screenField(coordinates(1920, 0), 100);
	screenField* pToBottomLefttCorner = new screenField(coordinates(0, 1080), 100);
	screenField* pToBottomRightCorner = new screenField(coordinates(1920, 1080), 100);

	pToMouseCursor->addObserver(pToTopLeftCorner);
	pToMouseCursor->addObserver(pToTopRightCorner);
	pToMouseCursor->addObserver(pToBottomLefttCorner);
	pToMouseCursor->addObserver(pToBottomRightCorner);

	std::thread mouseThread(mouseCursorPositionGetter, pToMouseCursor);

	mouseThread.join();
	return 0;
}