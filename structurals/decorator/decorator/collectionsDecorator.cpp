#include "collectionsDecorator.h"

void decorator::collectionFactory(collection* _pattern){
	if(dynamic_cast<naturalCollection*>(_pattern)){
		someCollection = new naturalCollection(limits.lowerLimit, limits.upperLimit);
	}
	else if(dynamic_cast<completeCollection*>(_pattern)){
		someCollection = new completeCollection(limits.lowerLimit, limits.upperLimit);
	}
	else if(true){
		std::cout << "Unknown collection type." << std::endl;
		terminate();
	}
}

decorator::~decorator(){
	delete someCollection;
}

naturalCollectionPrimeNumbersDecorator::naturalCollectionPrimeNumbersDecorator(naturalCollection* _collectionReference)
	: decorator(const_cast<const naturalCollection*>(_collectionReference)) {
	setAllegedLimits();
	if (!areLimitsValid()) {
		keepMonotonicity();
	}

	findPrimes();
}

void naturalCollectionPrimeNumbersDecorator::setAllegedLimits() {
	if(limits.lowerLimit < 2){
		limits.lowerLimit = 2;
	}
	limits.upperLimit = limits.upperLimit;
}

void naturalCollectionPrimeNumbersDecorator::findPrimes(){
	int number = static_cast<int>(limits.lowerLimit);
	int firstPrime = 2;

	do {
		if (number % 2) {
			float sqrtOfActualNumber = std::sqrt(number);
			int dividingCounter{ 0 };

			for (int i = firstPrime; i <= floor(sqrtOfActualNumber); i++) {
				if (!(number % i)) {
					dividingCounter++;
				}
			}

			if (dividingCounter < 1) {
				primes.push_back(number);
			}
		}
		++number;
	} while (number <= limits.upperLimit);
}

void naturalCollectionPrimeNumbersDecorator::showPrimes(){
	std::cout << "Primes in collection range from " << limits.lowerLimit << " to " << limits.upperLimit << ": " << std::endl;
	for(auto prime : primes){
		std::cout << prime << ", ";
	}
}