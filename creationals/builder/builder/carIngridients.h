#ifndef CARINGRIDIENTS_H
#define CARINGRIDIENTS_H

#include <string>

using std::string;

enum class gearType {manual = 0, semiauto, automatic};
enum class bodyType {SUV = 0, coupe, hatchback, sedan};

struct chassis{
public:
	short axlesNumber;
	int wheelbase;
	long bearingCapacity;
};

struct body{
public:
	bodyType type;
	string color;
	short partNumber;
};

struct engine{
public:
	float volume;
	short pistonNumber;
	long distance;
};

struct gearbox{
public:
	short gearsNumber;
	gearType type;
};

struct carInformations {
public:
	chassis chassisInfo;
	body bodyInfo;
	engine engineInfo;
	gearbox gearboxInfo;
};
#endif // CARINGRIDIENTS_H
