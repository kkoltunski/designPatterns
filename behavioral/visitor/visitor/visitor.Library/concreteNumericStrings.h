#ifndef CONCRETENUMERICSTRINGS_H
#define CONCRETENUMERICSTRINGS_H

#include "concreteVisitators.h"

class aritmeticString : public numericString {
public:
	aritmeticString(double _firstElementValue, double _factor);

	virtual double getN(size_t _elementNumber) override;
	virtual double getSum(size_t _firsElement, size_t _elementsNumberToSum) override;
	virtual void acceptMonoticityVisitor(numericStringVisitor* _visitator) override;
};

class geometricString : public numericString {
public:
	geometricString(double _firstElementValue, double _factor);

	virtual double getN(size_t _elementNumber) override;
	virtual double getSum(size_t _firsElement, size_t _elementsNumberToSum) override;
	virtual void acceptMonoticityVisitor(numericStringVisitor* _visitator) override;
};

#endif // CONCRETENUMERICSTRINGS_H