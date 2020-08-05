#include "concreteVisitators.h"

void numericStringMonoticityResearcher::visiAritmeticString(numericString* _recipient) {
	double n{ _recipient->getN(0) };
	double givenStringFactor{ _recipient->shareFactor() };
	short result{ 1 };
	bool previousComparisionResult{};

	if (givenStringFactor != 0) {
		for (size_t i = 0; i < minimumSamplesNumber; ++i) {
			double nPuls = n + givenStringFactor;
			bool comparisionResult = (nPuls > n ? true : false);

			if ((i > 0) && previousComparisionResult != comparisionResult) {
				throw(std::exception("Impossible case."));
			}

			n = nPuls;
			previousComparisionResult = comparisionResult;
		}

		result = previousComparisionResult ? growing : diminishing;
	}

	std::cout << "AritmeticString is " << monoticityDescriptions[result] << "." << std::endl;
}

void numericStringMonoticityResearcher::visitGeometricString(numericString* _recipient) {
	double n{ _recipient->getN(0) };
	double givenStringFactor{ _recipient->shareFactor() };
	short result{ 1 };
	bool previousComparisionResult{};

	if (givenStringFactor != 1) {
		for (size_t i = 0; i < minimumSamplesNumber; ++i) {
			double nPuls = n * givenStringFactor;
			bool comparisionResult = (nPuls > n ? true : false);

			if ((i > 0) && previousComparisionResult != comparisionResult) {
				result = undefined;
				break;
			}

			n = nPuls;
			previousComparisionResult = comparisionResult;
			result = previousComparisionResult ? growing : diminishing;
		}
	}

	std::cout << "GeometricString is " << monoticityDescriptions[result] << "." << std::endl;
}