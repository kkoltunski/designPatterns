#ifndef BASECLASSES_H
#define BASECLASSES_H

#include <list>

class observableObject;

class observer {
public:
	observer() = default;
	virtual void update(observableObject* _observable) = 0;
};

class observableObject {
protected:
	std::list<observer*> observersList;

	virtual void notify() = 0;

public:
	observableObject() = default;
	virtual ~observableObject() = default;

	void addObserver(observer* _observer);
	void removeObserver();
};

#endif // BASECLASSES_H