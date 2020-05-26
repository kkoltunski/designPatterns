#ifndef BOOKS_H
#define BOOKS_H

#include "genres.h"
extern std::vector<std::string> genresNames;

class iBook{
protected:
	virtual void getGenreDataReference() = 0;

	genre* data;

public:
	iBook(const std::string& _bookAuthor, const std::string& _bookName) : author(_bookAuthor), name(_bookName) {
	}

	std::string author;
	std::string name;
};

class novelBook : public iBook{
protected:
	inline virtual void getGenreDataReference() override{
		auto pToLib = genresStorage::getInstance();
		data = pToLib->getGenreData(departmentType::novel);
	}

public:
	novelBook(const std::string &_bookAuthor, const std::string &_bookName) : iBook(_bookAuthor, _bookName){
		getGenreDataReference();
	}
};

class scifiBook : public iBook {
protected:
	inline virtual void getGenreDataReference() override {
		auto pToLib = genresStorage::getInstance();
		data = pToLib->getGenreData(departmentType::sciience_fiction);
	}

public:
	scifiBook(const std::string& _bookAuthor, const std::string& _bookName) : iBook(_bookAuthor, _bookName) {
		getGenreDataReference();
	}
};

class horrorBook : public iBook {
protected:
	inline virtual void getGenreDataReference() override {
		auto pToLib = genresStorage::getInstance();
		data = pToLib->getGenreData(departmentType::horror);
	}

public:
	horrorBook(const std::string& _bookAuthor, const std::string& _bookName) : iBook(_bookAuthor, _bookName) {
		getGenreDataReference();
	}
};

class thrillerBook : public iBook {
protected:
	inline virtual void getGenreDataReference() override {
		auto pToLib = genresStorage::getInstance();
		data = pToLib->getGenreData(departmentType::thriller);
	}

public:
	thrillerBook(const std::string& _bookAuthor, const std::string& _bookName) : iBook(_bookAuthor, _bookName) {
		getGenreDataReference();
	}
};

class fantasyBook : public iBook {
protected:
	inline virtual void getGenreDataReference() override {
		auto pToLib = genresStorage::getInstance();
		data = pToLib->getGenreData(departmentType::fantasy);
	}

public:
	fantasyBook(const std::string& _bookAuthor, const std::string& _bookName) : iBook(_bookAuthor, _bookName) {
		getGenreDataReference();
	}
};

class classicBook : public iBook {
protected:
	inline virtual void getGenreDataReference() override {
		auto pToLib = genresStorage::getInstance();
		data = pToLib->getGenreData(departmentType::classic);
	}

public:
	classicBook(const std::string& _bookAuthor, const std::string& _bookName) : iBook(_bookAuthor, _bookName) {
		getGenreDataReference();
	}
};

class bookStorage{
private:
	void bookStorageInitialization();
	std::list<iBook*> allocatedBooks;
	std::vector<std::list<iBook*>> booksStorage;

public:
	bookStorage(){
		bookStorageInitialization();
	}
	virtual ~bookStorage();
	void addBook(std::string _author, std::string _name, departmentType _genre);	//factory
	void addBook(iBook *_bookToAdd);	//dangerous factory
	void showStorage();
};
#endif // BOOKS_H