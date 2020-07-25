#ifndef OBSERVER_H
#define OBSERVER_H

#include <Windows.h>
#include <iostream>

class observableObject;

class observer {
public:
	observer(observableObject* _observableObject);
	virtual void update() = 0;
};

#endif // BASECLASESS_H