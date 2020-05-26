#ifndef HEADER_H
#define HEADER_H

#include "books.h"

genresStorage& genresStorageReference = *(genresStorage::getInstance());
std::vector<std::string> genresNames{ "Novel", "SciFi", "Horror", "Thriller", "Fantasy", "Classic" };

#endif // HEADER_H