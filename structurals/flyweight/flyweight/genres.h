#ifndef GENRES_H
#define GENRES_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

enum class departmentType {
	novel = 0, sciience_fiction, horror, thriller, fantasy, classic,
	elementCount
	};

class genre {
private:
	explicit genre(departmentType _departmentType);
	inline void makeLocation() {
		location = 'A' + std::to_string(static_cast<int>(type));
	}
	int booksCount;
	int departmentCost;

public:
	std::string location;
	departmentType type;

	friend class genresStorage;
};

class genresStorage{
private:
	genresStorage(){
	}

	static genresStorage* makeInstance();
	static genresStorage* instance;

	genre* createGenre(departmentType _departmentType);
	genre* findGenre(departmentType _genreToFind);
	std::list<genre*> genres;

public:
	virtual ~genresStorage();
	static genresStorage* getInstance();
	genre* getGenreData(departmentType _genreToFind);
};

#endif // GENRES_H