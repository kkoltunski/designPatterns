#include "header.h"

int main(){
	userInterface UI{ settings::getInstance().get() };

	do {
		system("CLS");

		UI.actionPerformance();
		UI.showOptionsVectorInConsole();
		UI.keyFilter();

	} while (true);

	return 0;
}