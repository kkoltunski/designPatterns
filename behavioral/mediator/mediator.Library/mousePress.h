#ifndef MOUSEPRESS
#define MOUSEPRESS

#include "mediator.h"
#include <Windows.h>
#include <list>
#include <atomic>
#include <conio.h>

class mousePress : public eventBaseClass {
protected:
	void monitoring();
	mediator* pToMediator;

public:
	mousePress(mediator* _mediator = nullptr) : pToMediator{ _mediator } {
		if (pToMediator) {
			pToMediator->push_back(this);
		}
	}
	virtual ~mousePress() override = default;

	virtual void activate() override;
	virtual void deactivate() override;
	virtual bool isActivated() override {
		return m_eventRunning;
	}
};

#endif // MOUSEPRESS