#ifndef MP3FILEADAPTER_H
#define MP3FILEADAPTER_H

#include "formats.h"

class mp3FileAdapter : public mp3File, public iFormatValidator {
protected:
	virtual void formatValidation() override;

public:
	mp3FileAdapter(std::string _pathToFile) : mp3File(_pathToFile) {
		formatValidation();
	}
};

#endif