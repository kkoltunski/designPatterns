#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include <vector>
using std::vector;

//Template class for non-pointers types
template<typename T>
class storage {
private:
	vector<T> warehouse;

public:
	std::size_t push_back(T);
};

template<typename T>
std::size_t storage<T>::push_back(T _objectTypeAddress) {
	warehouse.push_back(_objectTypeAddress);

	return warehouse.size();
}

//Template class specialization for pointers types
template<typename T>
class storage<T*> {
private:
	vector<T*> warehouse;

public:
	virtual ~storage<T*>();

	std::size_t push_back(T*);
};

template<typename T>
std::size_t storage<T*>::push_back(T* _objectTypeAddress) {
	warehouse.push_back(_objectTypeAddress);

	return warehouse.size();
}

template<typename T>
storage<T*>::~storage<T*>() {
	for (unsigned int i = 0; i < warehouse.size(); i++) {
		delete warehouse[i];
	}
}

//Main factory template class
template<typename T>
class factory {
protected:
	storage<T*> storage;

public:
	virtual const T* factoryMethod(int _selector) = 0;
	virtual std::size_t pushToStorage(T* _objectTypeAddress);
};

template<typename T>
std::size_t factory<T>::pushToStorage(T* _objectTypeAddress) {
	return storage.push_back(_objectTypeAddress);
}

#endif // FACTORY_H