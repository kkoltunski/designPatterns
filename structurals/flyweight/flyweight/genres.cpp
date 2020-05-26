#include "genres.h"

genresStorage* genresStorage::instance{ nullptr };

genresStorage::~genresStorage() {
	std::for_each(instance->genres.begin(), instance->genres.end(), [](genre* pToGenre) {delete pToGenre; });
	delete instance;
}

genresStorage* genresStorage::makeInstance() {
	instance = new genresStorage();
	
	return instance;
}

genresStorage* genresStorage::getInstance() {
	genresStorage* pToLibrary = instance;

	if (instance == nullptr) {
		pToLibrary = makeInstance();
	}

	return pToLibrary;
}

genre* genresStorage::createGenre(departmentType _departmentType) {
	genre* pToGenre{ nullptr };

	try {
		pToGenre = new genre(_departmentType);
		genres.push_back(pToGenre);
	}
	catch (std::bad_alloc& exception) {
		std::cout << exception.what() << std::endl;
		terminate();
	}

	return pToGenre;
}

genre* genresStorage::findGenre(departmentType _genreToFind){
	genre* pToGenre{ nullptr };

	auto iteratorToGenre = std::find_if(genres.begin(), genres.end(), [&](genre* actualGenre) {return actualGenre->type == _genreToFind; });

	if (iteratorToGenre != genres.end()) {
		pToGenre = *iteratorToGenre;
	}

	return pToGenre;
}

genre* genresStorage::getGenreData(departmentType _genreToFind){
	genre* pToGenre = findGenre(_genreToFind);

	if (pToGenre == nullptr) {
		pToGenre = createGenre(_genreToFind);
	}

	return pToGenre;
}

genre::genre(departmentType _departmentType) : type{ _departmentType } {
	makeLocation();
}