#include "header.h"

int main(){

	naturalCollection natCollection(5, 100);
	natCollection.showCollectionIngridients();

	completeCollection compCollection(-10, 10);
	compCollection.showCollectionIngridients();

	naturalCollectionPrimeNumbersDecorator natCollDecorator(&natCollection);
	natCollDecorator.showCollectionIngridients();
	natCollDecorator.showPrimes();

	return 0;
}