#include "concreteNumericStrings.h"

aritmeticString::aritmeticString(double _firstElementValue, double _factor) : numericString(_firstElementValue, _factor) {
}

double aritmeticString::getN(size_t _elementNumber) {
	double result{ firstElement };

	inputParameterCorrection(_elementNumber);
	for (size_t i = 1; i < _elementNumber; ++i) {
		result += factor;
	}

	return result;
}

double aritmeticString::getSum(size_t _firsElement, size_t _elementsNumberToSum) {
	double nElement{ getN(_firsElement) };
	double result{ nElement };

	inputParameterCorrection(_elementsNumberToSum);
	for (size_t i = 1; i < _elementsNumberToSum; ++i) {
		double nextElement{ nElement + factor };
		nElement = nextElement;

		result += nextElement;
	}

	return result;
}

void aritmeticString::acceptMonoticityVisitor(numericStringVisitor* _visitator) {
	_visitator->visiAritmeticString(this);
}

geometricString::geometricString(double _firstElementValue, double _factor) : numericString(_firstElementValue, _factor) {
}

double geometricString::getN(size_t _elementNumber) {
	double result{ firstElement };

	inputParameterCorrection(_elementNumber);
	for (size_t i = 1; i < _elementNumber; ++i) {
		result *= factor;
	}

	return result;
}

double geometricString::getSum(size_t _firsElement, size_t _elementsNumberToSum) {
	double nElement{ getN(_firsElement) };
	double result{ nElement };

	inputParameterCorrection(_elementsNumberToSum);
	for (size_t i = 1; i < _elementsNumberToSum; ++i) {
		double nextElement{ nElement * factor };
		nElement = nextElement;

		result += nextElement;
	}

	return result;
}

void geometricString::acceptMonoticityVisitor(numericStringVisitor* _visitator) {
	_visitator->visitGeometricString(this);
}