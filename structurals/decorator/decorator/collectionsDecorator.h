#ifndef COLLECTIONSDECORATORS_H
#define COLLECTIONSDECORATORS_H

#include <cmath>
#include <list>
#include "collections.h"

//Collections decorator interface
class decorator : public collection{
private:
	void collectionFactory(collection* _pattern);

protected:
	inline virtual bool areLimitsValid() override{
		return someCollection->areLimitsValid();
	}
	virtual void setAllegedLimits() = 0;

	collection* someCollection;

public:
	decorator(const collection* _collectionPattern) : collection(*_collectionPattern){
		collectionFactory(const_cast<collection*>(_collectionPattern));
	}
	virtual ~decorator();
};

class naturalCollectionPrimeNumbersDecorator : public decorator{
private:
	void findPrimes();

protected:
	virtual void setAllegedLimits() override;

	std::list<int> primes;

public:
	explicit naturalCollectionPrimeNumbersDecorator(naturalCollection* _collectionReference);

	virtual void showPrimes();
};

#endif // COLLECTIONSDECORATORS_H