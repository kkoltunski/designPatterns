#ifndef VISITOR_H
#define VISITOR_H

#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include "numericString.h"

class numericStringVisitor{
public:
	virtual void visiAritmeticString(numericString* _recipient) = 0;
	virtual void visitGeometricString(numericString* _recipient) = 0;
};

#endif // VISITOR_H