#ifndef NUMERICSTRING_H
#define NUMERICSTRING_H

class numericStringVisitor;

class numericString{
protected:
	inline void inputParameterCorrection(size_t& _inputReference) {
		_inputReference = (_inputReference < 1 ? 1 : _inputReference);
	}

	double factor;
	double firstElement;

public:
	numericString(double _firstElementValue, double _factor);
	virtual ~numericString() = default;

	virtual double getN(size_t _elementNumber) = 0;
	virtual double getSum(size_t _firsElement, size_t _elementsNumberToSum) = 0;
	virtual void acceptMonoticityVisitor(numericStringVisitor* _visitator) = 0;

	inline double shareFactor() {
		return factor;
	}
};

#endif // NUMERICSTRING_H