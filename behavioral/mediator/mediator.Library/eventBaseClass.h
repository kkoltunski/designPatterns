#ifndef EVENTBASECLASS_H
#define EVENTBASECLASS_H

#include <functional>
#include <initializer_list>
#include <iostream>
#include <thread>

class mediator;

class eventBaseClass {
protected:
	std::thread m_eventThread;
	bool m_eventRunning;

public:
	eventBaseClass() : m_eventRunning{ false } {
	}
	virtual ~eventBaseClass();

	virtual void activate() = 0;
	virtual void deactivate() = 0;
	virtual bool isActivated() = 0;
};

#endif // EVENTBASECLASS_H