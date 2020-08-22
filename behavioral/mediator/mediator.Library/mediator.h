#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "eventBaseClass.h"
#include "taskExecutor.h"
#include <list>
#include <algorithm>

class timer;
class mousePress;
class userInterface;

class mediator{
protected:
	eventBaseClass* findEvent(size_t _eventIndex);
	std::list<eventBaseClass*> m_pToEvents;
	eventBaseClass* m_currentlyOn;
	const userInterface* pToMainSystem;
	taskExecutor* pToExecutor;

public:
	void reloadActiveEvent(size_t _eventIndex);
	void executorAssigment(taskExecutor* _pToExecutor) {
		pToExecutor = _pToExecutor;
	}
	void triggered();
	size_t push_back(eventBaseClass* _newEvent);
};

#endif // MEDIATOR_H