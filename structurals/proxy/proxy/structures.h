#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <fstream>
#include <string>

struct stream {
public:
	std::string path;
	std::fstream stream;
};

struct parameterData {
public:
	std::streampos byteInFile;
	std::size_t length;
};

#endif // STRUCTURES_H
