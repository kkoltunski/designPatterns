#include "timer.h"

std::function<void(timer*)> timer::m_lambdaDelay = [](timer* _t) {
	std::cout << "Synchronious event instaled." << std::endl;
	while (_t->m_eventRunning){
		while (_t->m_triggerDelay > (std::chrono::duration_cast<ms>(std::chrono::system_clock::now() - _t->m_startTimePoint).count())) {
		}
		_t->m_startTimePoint = std::chrono::system_clock::now();

		if (_t->pToMediator) {
			_t->pToMediator->triggered();
		}
		else {
			std::cout << "TRIGGER" << std::endl;
		}
	} 
};

timer::timer(const int _triggerDelay, mediator *_mediator)
	: m_triggerDelay{ _triggerDelay }, pToMediator{ _mediator }
{
	if (pToMediator) {
		pToMediator->push_back(this);
	}
}

void timer::activate() {
	m_eventRunning = true;
	if (!m_eventThread.joinable()) {
		m_startTimePoint = std::chrono::system_clock::now();
		m_eventThread = std::thread(m_lambdaDelay, this);
	}
}

void timer::deactivate() {
	m_eventRunning = false;
	m_eventThread.detach();

	m_startTimePoint = std::move(std::chrono::system_clock::time_point());
}