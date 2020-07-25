#ifndef SCREENFIELD_H
#define SCREENFIELD_H

#include "mouseCursor.h"

struct coordinates {
	size_t x;
	size_t y;

	coordinates(size_t _x, size_t _y) {
		x = _x;
		y = _y;
	}
};

class screenField : public observer {
private:
	void getDesktopResolution();
	void parametersControl();

	coordinates centerPosition;
	//int horizontalRange;
	//int verticalRange;
	size_t tolerance;
	unsigned int ID;

	static unsigned short horizontalResolution;
	static unsigned short verticalResolution;
	static unsigned int objectCounter;

public:
	screenField(coordinates &&_centerPosition, size_t&& _tolerance);
	virtual void update(observableObject* _observable) override;
};

#endif // SCREENFIELD_H