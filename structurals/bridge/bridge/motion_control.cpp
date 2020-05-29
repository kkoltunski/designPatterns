#include "motion_control.h"

stepperMotorControl::stepperMotorControl(int _stepsPerResolution) {
	try {
		motionUnit = new stepperMotor(_stepsPerResolution);
	}
	catch(std::bad_alloc &exception){
		std::cout << exception.what() << std::endl;
		terminate();
	}
}

int stepperMotorControl::angleToStepsCalculation(double _positionInRadians){
	auto pToStepperUnit = dynamic_cast<stepperMotor*>(motionUnit);

	double stepsPerResolution = static_cast<double>(pToStepperUnit->motion.stepsPerResolution);
	double anglePerStep = 360 / stepsPerResolution;
	double positionInAngle = ((_positionInRadians * 180) / PI);

	return static_cast<int>(positionInAngle / anglePerStep);
}

void stepperMotorControl::autoRotateClockwise(int _positionAsStep) {
	motionUnit->rotateClockwise(_positionAsStep);
}

void stepperMotorControl::autoRotateAnticlockwise(int _positionAsStep) {
	motionUnit->rotateAnticlockwise(_positionAsStep);
}

void stepperMotorControl::autoMovement(double _positionInRadians){
	setAutomaticOperatingMode();
	setAbsoluteMeasuringProfile();

	int destinationPositionInSteps = angleToStepsCalculation(_positionInRadians);

	if(destinationPositionInSteps < 0){
		autoRotateAnticlockwise(destinationPositionInSteps);
	}
	else{
		autoRotateClockwise(destinationPositionInSteps);
	}
}

void stepperMotorControl::manRotateClockwise(int _offset){
	setManualOperatingMode();
	setRelativeMeasuringProfile();
	motionUnit->rotateClockwise(_offset);
}

void stepperMotorControl::manRotateAnticlockwise(int _offset){
	setManualOperatingMode();
	setRelativeMeasuringProfile();

	if(_offset < 0){
		_offset = std::abs(_offset);
	}

	motionUnit->rotateAnticlockwise(-_offset);
}

void stepperMotorControl::setAbsoluteMeasuringProfile() {
	auto pToStepperUnit = dynamic_cast<stepperMotor*>(motionUnit);
	pToStepperUnit->motion.measuring.changeToAbsolute();
}
void stepperMotorControl::setRelativeMeasuringProfile() {
	auto pToStepperUnit = dynamic_cast<stepperMotor*>(motionUnit);
	pToStepperUnit->motion.measuring.changeToRelative();
}

void stepperMotorControl::setManualOperatingMode() {
	auto pToStepperUnit = dynamic_cast<stepperMotor*>(motionUnit);
	pToStepperUnit->mode.changeToManual();
}

void stepperMotorControl::setAutomaticOperatingMode() {
	auto pToStepperUnit = dynamic_cast<stepperMotor*>(motionUnit);
	pToStepperUnit->mode.changeToAutomatic();
}
