#include "header.h"

int main() {

	concreteCorrectPrism x(4, 5, 5);
	std::cout << "Base area = " << x.getBaseArea() << std::endl;
	std::cout << "Total area = " << x.getTotalArea() << std::endl;
	std::cout << "Side wall area = " << x.getSideWallArea() << std::endl;
	std::cout << "Volume = " << x.getVolume() << std::endl;

	std::shared_ptr<prism> pToPrism1 = x.cloneRequest();
	std::cout << "First cloned object address = " << pToPrism1 << std::endl;
	std::shared_ptr<prism> pToPrism2 = x.cloneRequest();
	std::cout << "Second cloned object address = " << pToPrism2 << std::endl;
	std::shared_ptr<prism> pToPrism3 = x.cloneRequest();
	std::cout << "Third cloned object address = " << pToPrism3 << std::endl;
	std::shared_ptr<prism> pToPrism4 = x.cloneRequest();
	std::cout << "Fourth cloned object address = " << pToPrism4 << std::endl;
	std::shared_ptr<prism> pToPrism5 = x.cloneRequest();
	std::cout << "Fifth cloned object address = " << pToPrism5 << std::endl;
	std::shared_ptr<prism> pToPrism6 = x.cloneRequest();
	std::cout << "Sixth cloned object address = " << pToPrism6 << std::endl;

	return 0;
}