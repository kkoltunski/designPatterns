#ifndef CARINFOBUILDER_H
#define CARINFOBUILDER_H

#include "carIngridients.h"
#include <iostream>
#include <memory>

//builder interface
class carInfoBuilder {
protected:
	virtual void chassisAssemble(short _axlesNumber, int _wheelbase, long _bearingCapacity);
	virtual void bodyAssemble(bodyType _type, string _color, short _partNumber);
	virtual void gearboxAssemble(short _gearsNumber, gearType _type);
	virtual void engineAssemble(float _volume, short _pistonNumber, long _distance);

	carInformations readyInformations;

public:
	virtual std::shared_ptr<carInformations> getResult() {
		return std::make_shared<carInformations>(readyInformations);
	}
	virtual void buildParts() = 0;
};

//builder director
class carInfoDirector{
private:
	carInfoBuilder* builder;

public:
	carInfoDirector(carInfoBuilder* _type);
	virtual ~carInfoDirector(){
		delete builder;
	}

	std::shared_ptr<carInformations> construct();
};

//concrete builders
class whiteSedanBuilder : public carInfoBuilder {
protected:
	virtual void buildParts() override;

public:
	whiteSedanBuilder(){
		buildParts();
	}
};

class redCoupeBuilder : public carInfoBuilder {
protected:
	virtual void buildParts() override;

public:
	redCoupeBuilder(){
		buildParts();
	}
};

class blackSUVBuilder : public carInfoBuilder {
protected:
	virtual void buildParts() override;

public:
	blackSUVBuilder(){
		buildParts();
	}
};


#endif // CARINFOBUILDER_H