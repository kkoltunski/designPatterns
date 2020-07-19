#ifndef LIMIT_H
#define LIMIT_H

enum class aligment : char { nearestBorder = 0, circle = 1 };

template<typename T>
class limit{
private:
	const T upperLimit;
	const T bottomLimit;

public:
	limit(T _bottomLimit, T _upperLimit);
	bool checkIfFit(T _value) const;
	bool adjustIfDoesnttMatch(T& _value, aligment fitDirection = aligment::circle) const;
};

template<typename T>
limit<T>::limit(T _bottomLimit, T _upperLimit)
	: bottomLimit{ _bottomLimit }, upperLimit{ _upperLimit }{
}

template<typename T>
bool limit<T>::checkIfFit(T _value) const{
	bool result{ true };

	if ((_value > upperLimit) || (_value < bottomLimit)) {
		result = false;
	}

	return result;
}

template<typename T>
bool limit<T>::adjustIfDoesnttMatch(T& _value, aligment fitDirection) const {
	bool result{ false };

	if (!checkIfFit(_value)) {
		if (_value >= upperLimit) {
			_value = (static_cast<char>(fitDirection) ? bottomLimit : upperLimit);
		}
		else if (_value <= bottomLimit) {
			_value = (static_cast<char>(fitDirection) ? upperLimit : bottomLimit);
		}

		result = true;
	}

	return result;
}

#endif // LIMIT_H