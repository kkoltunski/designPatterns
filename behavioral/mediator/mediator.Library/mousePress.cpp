#include "mousePress.h"

void mousePress::monitoring() {
	std::cout << "Mouse monitoring instaled." << std::endl;
	while (m_eventRunning){
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) {
			if (pToMediator) {
				pToMediator->triggered();
			}
			else {
				std::cout << "TRIGGER" << std::endl;
			}
		}
	} 
}

void mousePress::activate() {
	m_eventRunning = true;
	if (!m_eventThread.joinable()) {
		m_eventThread = std::thread{ [this] {monitoring(); } };
	}
}

void mousePress::deactivate() {
	m_eventRunning = false;
	if (m_eventThread.joinable()) {
		m_eventThread.join();
	}
}