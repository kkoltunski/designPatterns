#ifndef ENGINES_H
#define ENGINES_H

#include <string>
#include <list>
#include <iostream>
#include "structures.h"

class motor{
public:
	virtual void rotateClockwise(int) = 0;
	virtual void rotateAnticlockwise(int) = 0;

	workData mode;
};

class stepperMotor final : public motor {
private:
	void absoluteModeCalculation(int &_steps);
	void relativeModeCalculation(int &_steps);
	void actualPositionUpdate(int _steps);

public:
	explicit stepperMotor(int _stepsPerResolution) : motion(_stepsPerResolution){
	}
	virtual void rotateClockwise(int _steps) override;
	virtual void rotateAnticlockwise(int _steps) override;

	motionData motion;
};

#endif // ENGINES_H