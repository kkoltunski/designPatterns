#ifndef MOUSECURSOR_H
#define MOUSECURSOR_H

#include <iostream>
#include <Windows.h>
#include <algorithm>
#include "baseClasses.h"

class mouseCursor : public observableObject {
private:
	POINT position;
	virtual void notify() override;

public:
	bool setStateIfDifferent(POINT _position);
	inline POINT getState() {
		return position;
	}
};

#endif // MOUSECURSOR_H