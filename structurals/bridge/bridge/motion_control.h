#ifndef MOTIONCONTROL_H
#define MOTIONCONTROL_H

#include "motors.h"
constexpr double PI = 3.1415;

class iMotionControl {
protected:
	motor* motionUnit;

public:
	iMotionControl() : motionUnit(nullptr){
	}
	virtual ~iMotionControl() = default;
	virtual void autoRotateClockwise(int) = 0;
	virtual void autoRotateAnticlockwise(int) = 0;
	virtual void manRotateClockwise(int) = 0;
	virtual void manRotateAnticlockwise(int) = 0;
};

class stepperMotorControl final : public iMotionControl{
private:
	int angleToStepsCalculation(double _positionInRadians);
	void setAbsoluteMeasuringProfile();
	void setRelativeMeasuringProfile();
	void setManualOperatingMode();
	void setAutomaticOperatingMode();
	virtual void autoRotateClockwise(int _positionAsStep) override;
	virtual void autoRotateAnticlockwise(int _positionAsStep) override;

public:
	explicit stepperMotorControl(int _stepsPerResolution);
	virtual ~stepperMotorControl() override{
		delete motionUnit;
	}

	void autoMovement(double _positionInRadians);
	virtual void manRotateClockwise(int _offset) override;
	virtual void manRotateAnticlockwise(int _offset) override;

};
#endif // MOTIONCONTROL_H