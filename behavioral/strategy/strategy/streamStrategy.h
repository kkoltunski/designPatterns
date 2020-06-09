#ifndef STREAMSTRATEGY_H
#define STREAMSTRATEGY_H

#include "boostedFstream.h"

//filestream formating interface & operations
class filestreamFormatingStrategy {
protected:
	std::string workSpace;

public:
	filestreamFormatingStrategy() : workSpace(""){
	}
	virtual void operation(boostedFstream* const _streamPtr) = 0;
};

class filestreamToUpper : public filestreamFormatingStrategy {
public:
	virtual void operation(boostedFstream* const _streamPtr) override;
};

class filestreamToLower : public filestreamFormatingStrategy {
public:
	virtual void operation(boostedFstream* const _streamPtr) override;
};

class filestreamSeparator : public filestreamFormatingStrategy {
private:
	bool areIndexesInRange(char _actualChar, char _nextChar);
	char separator;

public:
	filestreamSeparator(char _separator) : separator{ _separator }{
	}
	virtual void operation(boostedFstream* const _streamPtr) override;
};

#endif // STREAMSTRATEGY_H