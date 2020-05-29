#include "header.h"

int main(){

	stepperMotorControl motion1(512);

	motion1.autoMovement(-1);
	motion1.autoMovement(0.5);
	motion1.autoMovement(2);
	motion1.autoMovement(-3);
	motion1.autoMovement(8);
	motion1.autoMovement(0);
	motion1.manRotateAnticlockwise(1);
	motion1.manRotateClockwise(10);
	motion1.manRotateAnticlockwise(150);

	return 0;
}