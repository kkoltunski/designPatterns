#ifndef FORMATS_H
#define FORMATS_H

#include "interfaces.h"

class flacFile : public iFormatValidator {
protected:
	virtual void formatValidation() override;

	iFileStream file;

public:
	explicit flacFile(const std::string &_pathToFile);
};

/*For example - this class can not be modifyed (library or so).
Thats why iFormatValidator can not be implemented and adapter is necessary to validate opened file*/
class mp3File{
protected:
	iFileStream file;

public:
	explicit mp3File(const std::string &_pathToFile);
};

#endif // FORMATS_H