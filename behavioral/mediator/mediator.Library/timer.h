#ifndef TIMER_H
#define TIMER_H

#include "mediator.h"
#include <chrono>

class timer : public eventBaseClass {
protected:
	typedef std::chrono::milliseconds ms;

	std::chrono::system_clock::time_point m_startTimePoint;
	static std::function<void(timer*)> m_lambdaDelay;
	const int m_triggerDelay;
	mediator* pToMediator;

public:
	timer(const int _triggerDelay, mediator* _mediator = nullptr);
	virtual ~timer() override = default;

	virtual void activate() override;
	virtual void deactivate() override;
	virtual bool isActivated() override {
		return std::chrono::duration_cast<ms>(m_startTimePoint.time_since_epoch()).count();
	}
};

#endif // TIMER_H