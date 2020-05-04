#include "prism.h"

concreteCorrectPrism::concreteCorrectPrism(int _baseVertices, int _baseSideLength, int height) : correctPrism(_baseVertices, height, _baseSideLength) {
	sideWallAreaCalculation();
	baseAreaCalculation();
	totalAreaCalculation();
	volumeCalculation();
}

concreteCorrectPrism::concreteCorrectPrism(concreteCorrectPrism &_original) : correctPrism(_original) {
	volume = _original.volume;
	baseArea = _original.baseArea;
	totalArea = _original.totalArea;
	sideWallArea = _original.sideWallArea;
}

void concreteCorrectPrism::baseAreaCalculation() {
	//patterns and this function are not a purpose of "project"
	switch (baseVertices) {
	case 3:
		baseArea = (baseSideLength * baseSideLength);
		break;
	case 4:
		baseArea = (baseSideLength * baseSideLength);
		break;
	default:
		baseArea = (baseSideLength * baseSideLength);
		break;
	}
}

std::shared_ptr<prism> concreteCorrectPrism::clone() {
	try {
		std::shared_ptr<prism> pToPrism{std::make_shared<concreteCorrectPrism>(*this)};
		return pToPrism;
	}
	catch (std::bad_alloc& exception) {
		std::cout << exception.what() << std::endl;
		terminate();
	}
}