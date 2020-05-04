#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <list>
#include <algorithm>

template<typename T>
class prototypeManager {
protected:
	std::list<std::shared_ptr<T>> prototypeObjects;
	//virtual ~prototypeManager();								//In case of use non-smart pointers

public:
	std::shared_ptr<T> pushToTheEnd(std::shared_ptr<T> _object);
};

//template<typename T>
//prototypeManager<T>::~prototypeManager() {
//	std::for_each(prototypeObjects.begin(), prototypeObjects.end(), [](T *pToElement) {delete pToElement; });
//} 

template<typename T>
std::shared_ptr<T> prototypeManager<T>::pushToTheEnd(std::shared_ptr<T> _object) {
	prototypeObjects.push_back(_object);

	return _object;
}

template<typename T>
class prototype {
protected:
	virtual std::shared_ptr<T> clone() = 0;
};

#endif // PROTOTYPE_H