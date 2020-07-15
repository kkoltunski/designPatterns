#include "header.h"

int main(){
	userInterface UI{ settings::getInstance().get() };

	do {
		UI.showProfileNamesContentInConsole();
		UI.showOptionsVectorInConsole();
		UI.getKey();

	} while (true);

	return 0;
}