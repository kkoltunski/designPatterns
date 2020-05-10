#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <exception>

struct openingFileFail : public std::exception {
private:
	std::string MSG;

public:
	openingFileFail(const std::string _filePath) {
		MSG = "Opening file " + _filePath + "failed.";
	}

	virtual const char* what() const override {
		return MSG.c_str();
	}
};

struct streamIsBroken : public std::exception {
private:
	std::string MSG;

public:
	streamIsBroken() {
		MSG = "Stream is in fail state.";
	}

	virtual const char* what() const override {
		return MSG.c_str();
	}
};

#endif // ERRORHANDLING_H