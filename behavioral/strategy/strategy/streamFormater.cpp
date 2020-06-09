#include "streamFormater.h"

bool filestreamFormater::isOperationAble(){
	return (streamPtr->is_open() && !streamPtr->fail());
}

void filestreamFormater::operation(filestreamFormatingStrategy* _strategyFormat) {
	_strategyFormat->operation(streamPtr);
}