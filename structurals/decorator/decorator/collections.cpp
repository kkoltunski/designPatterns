#include "collections.h"

collection::collection(float _bottomLimit, float _upperLimit) {
	limits.lowerLimit = _bottomLimit;
	limits.upperLimit = _upperLimit;
}

void collection::keepMonotonicity(){
	if(limits.lowerLimit > limits.upperLimit){
		float temp{ limits.upperLimit };

		limits.upperLimit = limits.lowerLimit;
		limits.lowerLimit = temp;
	}
}

void collection::showCollectionIngridients(){
	float actualValue = limits.lowerLimit;

	do{
		std::cout << actualValue;

		if(!(actualValue == limits.upperLimit)){
			std::cout << ", ";
		}
		else{
			std::cout << std::endl;
		}

		actualValue++;
	} while (actualValue <= limits.upperLimit);
}

naturalCollection::naturalCollection(float _bottomLimit, float _upperLimit) : collection(_bottomLimit, _upperLimit){
	if (!areLimitsValid()) {
		setAllegedLimits();
	}
	else {
		keepMonotonicity();
	}
}

bool naturalCollection::areLimitsValid(){
	bool result{ false };

	if(limits.lowerLimit >= 0){
		if(limits.upperLimit >= 0){
			if((ceil(limits.lowerLimit) == limits.lowerLimit) || (floor(limits.lowerLimit) == limits.lowerLimit)){
				if((ceil(limits.upperLimit) == limits.upperLimit) || (floor(limits.upperLimit) == limits.upperLimit)){
					result = true;
				}
			}
		}
	}

	return result;
}

void naturalCollection::setAllegedLimits(){
	limits.lowerLimit = 0;
	limits.upperLimit = static_cast<float>(std::numeric_limits<int>::max());
}

completeCollection::completeCollection(float _bottomLimit, float _upperLimit) : collection(_bottomLimit, _upperLimit) {
	if (!areLimitsValid()) {
		setAllegedLimits();
	}
	else {
		keepMonotonicity();
	}
}

bool completeCollection::areLimitsValid(){
	bool result{ false };

	if ((ceil(limits.lowerLimit) == limits.lowerLimit) || (floor(limits.lowerLimit) == limits.lowerLimit)) {
		if ((ceil(limits.upperLimit) == limits.upperLimit) || (floor(limits.upperLimit) == limits.upperLimit)) {
			result = true;
		}
	}

	return result;
}

void completeCollection::setAllegedLimits() {
	limits.lowerLimit = static_cast<float>(std::numeric_limits<int>::min());
	limits.upperLimit = static_cast<float>(std::numeric_limits<int>::max());
}