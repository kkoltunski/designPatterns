#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include <iostream>
#include <limits>

struct range{
	float upperLimit;
	float lowerLimit;
};

//Main collection interface
class collection
{
protected:
	void keepMonotonicity();

	//virtual bool areLimitsValid() = 0;
	//virtual void setAllegedLimits() = 0;

	range limits;

public:
	collection(const collection &_someCollection){
		limits.lowerLimit = _someCollection.limits.lowerLimit;
		limits.upperLimit = _someCollection.limits.upperLimit;
	}
	collection(float _bottomLimit, float _upperLimit);
	virtual ~collection() = default;

	virtual bool areLimitsValid() = 0;
	virtual void setAllegedLimits() = 0;

	void showCollectionIngridients();
};

//Concrete collections
class naturalCollection : public collection{
protected:
	virtual bool areLimitsValid() override;
	virtual void setAllegedLimits() override;

public:
	naturalCollection(float _bottomLimit, float _upperLimit);
};

class completeCollection : public collection {
protected:
	virtual bool areLimitsValid() override;
	virtual void setAllegedLimits() override;

public:
	completeCollection(float _bottomLimit, float _upperLimit);
};

/*Real collections interface
class realCollection : public collection {
protected:
	std::list<float> numbersInRange;
	//float spaceBetweenNumbers;

public:
	realCollection(float _bottomLimit, float _upperLimit//, float _spaceBetweenNumber//) : collection(_bottomLimit, _upperLimit){
	}
};*/


#endif // COLLECTIONS_H