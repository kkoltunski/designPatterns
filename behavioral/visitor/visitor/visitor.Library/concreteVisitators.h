#ifndef CONCRETEVISITATORS_H
#define CONCRETEVISITATORS_H

#include "visitor.h"

enum magicNumbers { minimumSamplesNumber = 4 };

class numericStringMonoticityResearcher : public numericStringVisitor {
private:
	enum monoticity : char { diminishing = 0, constant, growing, undefined };
	std::vector<std::string> monoticityDescriptions{"diminishing", "constant", "growing", "undefined" };

public:
	virtual void visiAritmeticString(numericString* _recipient) override;
	virtual void visitGeometricString(numericString* _recipient) override;
};

#endif // CONCRETEVISITATORS_H