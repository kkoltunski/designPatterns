#include "header.h"

int main(){
	bookStorage library;

	novelBook firstBook("x", "xx");
	novelBook secondBook("y", "yy");
	horrorBook thirdBook("z", "zz");
	scifiBook fourthBook("o", "oo");
	horrorBook fifthBook("l", "ll");
	scifiBook sixthBook("v", "vv");

	library.addBook(&firstBook);
	library.addBook(&secondBook);
	library.addBook(&thirdBook);
	library.addBook(&fourthBook);
	library.addBook(&fifthBook);
	library.addBook(&sixthBook);

	library.addBook("Martin", "A Song of Ice and Fire", departmentType::fantasy);
	library.addBook("Tolkien", "Lord of the rings", departmentType::fantasy);
	library.addBook("King", "It", departmentType::horror);
	library.addBook("Ludlum", "Bourne identity", departmentType::thriller);

	library.showStorage();

	return 0;
}