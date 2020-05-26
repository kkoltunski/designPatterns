#include "books.h"

void bookStorage::bookStorageInitialization() {
	std::list<iBook*> temporaryList{};

	for (int i = 0; i < static_cast<int>(departmentType::elementCount); i++) {
		booksStorage.push_back(temporaryList);
	}
}

bookStorage::~bookStorage(){
	std::for_each(allocatedBooks.begin(), allocatedBooks.end(), [](iBook* pToBook) {delete pToBook; });
}

void bookStorage::addBook(std::string _author, std::string _name, departmentType _genre) {
	iBook* pToBook{ nullptr };

	try{
		switch (static_cast<int>(_genre)) {
		case 0:
			pToBook = new novelBook(_author, _name);
			break;
		case 1:
			pToBook = new scifiBook(_author, _name);
			break;
		case 2:
			pToBook = new horrorBook(_author, _name);
			break;
		case 3:
			pToBook = new thrillerBook(_author, _name);
			break;
		case 4:
			pToBook = new fantasyBook(_author, _name);
			break;
		case 5:
			pToBook = new classicBook(_author, _name);
			break;
		default:
			std::cout << "Unknown book genre." << std::endl;
			break;
		}

		if (pToBook != nullptr) {
			allocatedBooks.push_back(pToBook);
			booksStorage[static_cast<int>(_genre)].push_back(pToBook);
		}
	}
	catch(std::bad_alloc &exception){
		std::cout << exception.what() << std::endl;
		terminate();
	}
}

/*Dengerous overload - additional book storage should exist for elements added by this method
because destructor will delete books created by this storage and memory leak or access violation can appear*/
void bookStorage::addBook(iBook* _bookToAdd) {
	if(dynamic_cast<novelBook*>(_bookToAdd)){
		booksStorage[static_cast<int>(departmentType::novel)].push_back(_bookToAdd);
	}
	else if(dynamic_cast<scifiBook*>(_bookToAdd)){
		booksStorage[static_cast<int>(departmentType::sciience_fiction)].push_back(_bookToAdd);
	}
	else if (dynamic_cast<horrorBook*>(_bookToAdd)) {
		booksStorage[static_cast<int>(departmentType::horror)].push_back(_bookToAdd);
	}
	else if (dynamic_cast<thrillerBook*>(_bookToAdd)) {
		booksStorage[static_cast<int>(departmentType::thriller)].push_back(_bookToAdd);
	}
	else if (dynamic_cast<fantasyBook*>(_bookToAdd)) {
		booksStorage[static_cast<int>(departmentType::fantasy)].push_back(_bookToAdd);
	}
	else if (dynamic_cast<classicBook*>(_bookToAdd)) {
		booksStorage[static_cast<int>(departmentType::classic)].push_back(_bookToAdd);
	}
}

void bookStorage::showStorage(){
	for(int i = 0; i < static_cast<int>(departmentType::elementCount); i++){
		std::cout << genresNames[i] << "books : " << std::endl;

		for (auto x = booksStorage[i].begin(); x != booksStorage[i].end(); x++) {
			std::cout << "\t- " << (*x)->author << ", " << (*x)->name << std::endl;
		}
	}
}