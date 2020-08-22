#include "eventBaseClass.h"

eventBaseClass::~eventBaseClass() {
	if (m_eventThread.joinable()) {
		m_eventThread.join();
	}
}