#include <memory>
#include "header.h"

int main() {
	numericStringVisitor* pToNumericStringVisitor = new numericStringMonoticityResearcher();

	std::vector<numericString*> numericStringsContainer;
	numericStringsContainer.push_back(new aritmeticString(1.5, -0.5));
	numericStringsContainer.push_back(new aritmeticString(8.25, 0));
	numericStringsContainer.push_back(new aritmeticString(-100, 28));
	numericStringsContainer.push_back(new geometricString(-2, -2));
	numericStringsContainer.push_back(new geometricString(-2, 2));
	numericStringsContainer.push_back(new geometricString(-0.25, 1));
	numericStringsContainer.push_back(new geometricString(0.324, 100));

	for (auto numericString : numericStringsContainer) {
		numericString->acceptMonoticityVisitor(pToNumericStringVisitor);
	}

	std::for_each(std::begin(numericStringsContainer), std::end(numericStringsContainer),
		[](numericString* _numericString) {delete _numericString; });
	delete pToNumericStringVisitor;

	return 0;
}