#ifndef PRISM_H
#define PRISM_H

#include "iostream"
#include "prototype.h"

class prism
{
protected:
	inline virtual void volumeCalculation() {
		volume = (baseArea * height);
	}
	inline virtual void totalAreaCalculation() {
		totalArea = (2 * baseArea) + (4 * sideWallArea);
	};
	virtual void baseAreaCalculation() = 0;
	virtual void sideWallAreaCalculation() = 0;

	int volume;
	int baseArea;
	int totalArea;
	int sideWallArea;
	int height;

public:
	prism(int _height) : height { _height }{
	}
	prism(prism& _original) : height{ _original.height } {
	}
	
	virtual std::shared_ptr<prism> cloneRequest() = 0;
};

class correctPrism : public prism
{
protected:
	inline virtual void sideWallAreaCalculation() override{
		sideWallArea = (height * baseSideLength);
	}
	int baseVertices;
	int baseSideLength;

public:
	correctPrism(int _baseVertices, int _height, int _baseSideLength)
		: prism(_height), baseVertices{ _baseVertices }, baseSideLength{ _baseSideLength } {
	}
	correctPrism(correctPrism& _original) : prism(_original), baseVertices{ _original.baseVertices}, baseSideLength{ _original.baseSideLength}{
	}
};

class concreteCorrectPrism : public correctPrism, public prototype<prism>, public prototypeManager<prism>
{
protected:
	virtual void baseAreaCalculation() override;
	virtual std::shared_ptr<prism> clone() override;

public:
	concreteCorrectPrism(int _baseVertices, int _baseSideLength, int height);
	concreteCorrectPrism(concreteCorrectPrism &_original);

	inline virtual std::shared_ptr<prism> cloneRequest() override {
		return pushToTheEnd(clone());
	}

	inline int getBaseArea() {
		return baseArea;
	}
	inline int getTotalArea() {
		return totalArea;
	}
	inline int getVolume() {
		return volume;
	}
	inline int getSideWallArea() {
		return sideWallArea;
	}
};


#endif //PRISM_H