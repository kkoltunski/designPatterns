#include "motors.h"

void stepperMotor::absoluteModeCalculation(int &_steps){
	if((_steps < 0) && (motion.actualPosition == 0)){
		_steps = motion.stepsPerResolution + _steps;
	}

	_steps = std::abs(_steps);
}

void stepperMotor::relativeModeCalculation(int &_steps){
	_steps = motion.actualPosition + _steps;

	if (_steps < 0) {
		_steps = motion.stepsPerResolution + _steps;
	}
	else if (_steps > motion.stepsPerResolution){
		_steps %= motion.stepsPerResolution;
	}
}

void stepperMotor::actualPositionUpdate(int _steps){
	_steps %= motion.stepsPerResolution;

	if (motion.isRelativeMeasuringOn()) {
		relativeModeCalculation(_steps);
	}
	else {
		absoluteModeCalculation(_steps);
	}

	motion.actualPosition = _steps;
}

void stepperMotor::rotateClockwise(int _steps){
	motion.movement = motionData::action::clockwise;
	actualPositionUpdate(_steps);

	std::cout << "Stepper motor : " << this << std::endl;
	std::cout << "Operating mode : " << (static_cast<bool>(mode.operatingMode) ? "manual" : "automatic") << std::endl;
	std::cout << "Measuring mode : " << (static_cast<bool>(motion.measuring.mode) ? "relative" : "absolute") << std::endl;
	std::cout << "Actual position : " << motion.actualPosition << std::endl;
	std::cout << "Clockwise movement\n" << std::endl;

	motion.movement = motionData::action::stop;
}

void stepperMotor::rotateAnticlockwise(int _steps){
	motion.movement = motionData::action::anticlockwise;
	actualPositionUpdate(_steps);

	std::cout << "Stepper motor : " << this << std::endl;
	std::cout << "Operating mode : " << (static_cast<bool>(mode.operatingMode) ? "manual" : "automatic") << std::endl;
	std::cout << "Measuring mode : " << (static_cast<bool>(motion.measuring.mode) ? "relative" : "absolute") << std::endl;
	std::cout << "Actual position : " << motion.actualPosition << std::endl;
	std::cout << "Anticlockwise movement\n" << std::endl;

	motion.movement = motionData::action::stop;
}
