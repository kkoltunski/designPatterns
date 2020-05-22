#ifndef HEADER_H
#define HEADER_H

#include "importantFile.h"

bool passedArgumentsNumberCorrect(int _argc){
	bool result{ true };

	try{
		if (_argc < 2) {
			result = false;
			throw(std::exception("Parameters number is not correct.\n"));
		}
	}
	catch(std::exception& exception){
		std::cout << exception.what() << std::endl;
		terminate();
	}

	return result;
}

#endif // HEADER_H