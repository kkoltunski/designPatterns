#include "header.h"

int main() {
	compositeFactory compositeFactory;
	compositeFactory.factoryMethod(1);
	compositeFactory.factoryMethod(1);
	compositeFactory.factoryMethod(2);
	compositeFactory.factoryMethod(2);
	compositeFactory.factoryMethod(1);
	compositeFactory.factoryMethod(3);

	return 0;
}