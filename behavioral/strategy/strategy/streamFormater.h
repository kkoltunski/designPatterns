#ifndef STREAMFORMATER_H
#define STREAMFORMATER_H

#include "streamStrategy.h"
#include <string>

class filestreamFormater {
protected:
	filestreamFormater() = default;
	virtual bool isOperationAble();

	boostedFstream* const streamPtr;

public:
	filestreamFormater(boostedFstream& _streamReference) : streamPtr(&_streamReference) {
	}
	virtual void operation(filestreamFormatingStrategy* _strategyFormat);
};


#endif // STREAMFORMATER_H