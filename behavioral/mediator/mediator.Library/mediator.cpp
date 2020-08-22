#include "mediator.h"

eventBaseClass* mediator::findEvent(size_t _eventIndex) {
	eventBaseClass* result{};

	for (auto it = std::begin(m_pToEvents); it != std::end(m_pToEvents); ++it) {
		if (_eventIndex == (std::distance(std::begin(m_pToEvents), it))) {
			result = (*it);
		}
	}

	return result;
}

void mediator::reloadActiveEvent(size_t _eventIndex) {
	eventBaseClass* pToIndexedEvent{ findEvent(_eventIndex)};

	if (m_currentlyOn && (pToIndexedEvent != m_currentlyOn)) {
		m_currentlyOn->deactivate();
	}

	pToIndexedEvent->activate();
	m_currentlyOn = pToIndexedEvent;
}

void mediator::triggered() {
	pToExecutor->doStuff();
}

size_t mediator::push_back(eventBaseClass* _newEvent) {
	bool isUniqe = all_of(std::begin(m_pToEvents), std::end(m_pToEvents), 
		[&](const eventBaseClass* _p) {return (_p != _newEvent); });
	int result{ -1 };

	if (isUniqe) {
		m_pToEvents.push_back(_newEvent);
		result += m_pToEvents.size();
	}

	if (result == -1) {
		throw(std::exception("Event installed."));
	}

	return result;
}