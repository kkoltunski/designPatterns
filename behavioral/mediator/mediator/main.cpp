#include "header.h"

int main() {
	mediator* pToEventHandler{ userInterface::instance()->shareEventHandler() };
	timer synchroniusEvent(3000, pToEventHandler);
	mousePress mousePressEvent{pToEventHandler };
	taskExecutor cpuMeasurment;
	pToEventHandler->executorAssigment(&cpuMeasurment);

	do {
		userInterface::instance()->showUserDialog();
	} while (1);

	return 0;
}