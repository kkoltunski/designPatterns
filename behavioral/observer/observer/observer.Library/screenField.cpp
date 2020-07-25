#include "screenField.h"

unsigned short screenField::horizontalResolution{ 0 };
unsigned short screenField::verticalResolution{ 0 };
unsigned int screenField::objectCounter{ 0 };

screenField::screenField(coordinates&& _center, size_t&& _tolerance) : centerPosition{ _center }, tolerance{ _tolerance }, ID{ objectCounter }{
	if (!horizontalResolution || !verticalResolution) {
		getDesktopResolution();
	}

	parametersControl();
	objectCounter++;
}

void screenField::update(observableObject* _observable) {
	POINT observablePosition = dynamic_cast<mouseCursor*>(_observable)->getState();

	if (tolerance >= abs(static_cast<short>(observablePosition.x) - static_cast<short>(centerPosition.x))) {
		if (tolerance >= abs(static_cast<short>(observablePosition.y) - static_cast<short>(centerPosition.y))) {
			std::cout << "Mouse detected in field" << ID << "." << std::endl;
		}
	}
}

void screenField::getDesktopResolution() {
	RECT desktop;

	const HWND hDesktop = GetDesktopWindow(); //handler to desktop
	GetWindowRect(hDesktop, &desktop); //load screen resolution into desktop

	horizontalResolution = static_cast<unsigned short>(desktop.right);
	verticalResolution = static_cast<unsigned short>(desktop.bottom);
}

void screenField::parametersControl() {
	centerPosition.x = (centerPosition.x > horizontalResolution ? horizontalResolution : centerPosition.x);
	centerPosition.y = (centerPosition.y > verticalResolution ? verticalResolution : centerPosition.y);
}
