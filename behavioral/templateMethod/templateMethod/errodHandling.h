#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <exception>

class wrongData : public std::exception{
private:
	std::string MSG;

public:
	wrongData(const std::string& _message) : MSG(_message){
	}
	virtual const char* what() const noexcept{
		return MSG.c_str();
	}
};

#endif //ERRORHANDLING_H