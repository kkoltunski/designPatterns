#include "carInfoBuilder.h"

void carInfoBuilder::chassisAssemble(short _axlesNumber, int _wheelbase, long _bearingCapacity) {
	readyInformations.chassisInfo.axlesNumber = _axlesNumber;
	readyInformations.chassisInfo.wheelbase = _wheelbase;
	readyInformations.chassisInfo.bearingCapacity = _bearingCapacity;
}
void carInfoBuilder::bodyAssemble(bodyType _type, string _color, short _partNumber) {
	readyInformations.bodyInfo.type = _type;
	readyInformations.bodyInfo.color = _color;
	readyInformations.bodyInfo.partNumber = _partNumber;
}
void carInfoBuilder::gearboxAssemble(short _gearsNumber, gearType _type) {
	readyInformations.gearboxInfo.gearsNumber = _gearsNumber;
	readyInformations.gearboxInfo.type = _type;
}
void carInfoBuilder::engineAssemble(float _volume, short _pistonNumber, long _distance) {
	readyInformations.engineInfo.volume = _volume;
	readyInformations.engineInfo.pistonNumber = _pistonNumber;
	readyInformations.engineInfo.distance = _distance;
}

carInfoDirector::carInfoDirector(carInfoBuilder* _type) : builder{nullptr} {
	if(dynamic_cast<whiteSedanBuilder*>(_type)){
		std::cout << "whiteSedanBuilder" << std::endl;
		builder = new whiteSedanBuilder();
	}
	else if(dynamic_cast<redCoupeBuilder*>(_type)){
		std::cout << "redCoupeBuilder" << std::endl;
		builder = new redCoupeBuilder();
	}
	else if(dynamic_cast<blackSUVBuilder*>(_type)){
		std::cout << "blackSUVBuilder" << std::endl;
		builder = new blackSUVBuilder();
	}
	else{
		std::cout << "Unknown builder specialization." << std::endl;
	}
}

std::shared_ptr<carInformations> carInfoDirector::construct() {
	builder->buildParts();

	return builder->getResult();
}

void whiteSedanBuilder::buildParts() {
	chassisAssemble(2, 2200, 1900);
	bodyAssemble(bodyType::sedan, "WHITE", 8);
	gearboxAssemble(6, gearType::manual);
	engineAssemble(static_cast<float>(2.2), 6, 0);
}

void redCoupeBuilder::buildParts() {
	chassisAssemble(2, 1800, 1300);
	bodyAssemble(bodyType::coupe, "RED", 6);
	gearboxAssemble(6, gearType::automatic);
	engineAssemble(static_cast<float>(1.8), 6, 0);
}

void blackSUVBuilder::buildParts() {
	chassisAssemble(4, 2200, 5000);
	bodyAssemble(bodyType::SUV, "BLACK", 10);
	gearboxAssemble(9, gearType::semiauto);
	engineAssemble(static_cast<float>(5.0), 12, 0);
}