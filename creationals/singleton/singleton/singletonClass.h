#ifndef SINGLETONCLASS_H
#define SINGLETONCLASS_H

template<typename T>
class singletonClass
{
private:
	singletonClass<T>() {
		try {
			singletonObject = new T();
		}
		catch (std::bad_alloc &exception) {
			std::cout << exception.what() << std::endl;
			terminate();
		}
	}
	~singletonClass<T>() {
		delete singletonObject;
	}

	static T* singletonObject;

public:
	static T *getInstance() {
		if (singletonObject == nullptr){
			singletonClass<T>();
		}

		return singletonObject;
	}

};

template<typename T>
T *singletonClass<T>::singletonObject{ nullptr };

#endif
