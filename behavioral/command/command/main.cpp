#include "header.h"

int main(){
	std::size_t commandIndex{};
	std::string fileName{};
	commandInvoker invoker;
	directory exampleDirectory{ pathToDirectory };
	fileCreator* pToFileCreator = new fileCreator(&exampleDirectory);
	directoryCreator* pToDirectoryCreator = new directoryCreator(&exampleDirectory);
	fileRemover* pToFileRemover = new fileRemover(&exampleDirectory);
	finisher* pToFinisher = new finisher();

	exampleDirectory.tryToCreate();
	invoker.addCommand(static_cast<std::size_t>(commands::fileCreator), pToFileCreator);
	invoker.addCommand(static_cast<std::size_t>(commands::directoryCreator), pToDirectoryCreator);
	invoker.addCommand(static_cast<std::size_t>(commands::fileRemover), pToFileRemover);
	invoker.addCommand(static_cast<std::size_t>(commands::finisher), pToFinisher);

	do{
		bool streamError{};
		invoker.showPossibilities();

		do{
			std::cout << "\nYour choose: ";
			std::cin >> commandIndex;
			streamError = std::cin.fail();

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		} while (streamError);

		if(commandIndex != (static_cast<std::size_t>(commands::finisher))){
			do {
				std::cout << "File name you want to use in choosen command: ";
				std::getline(std::cin, fileName);
				streamError = std::cin.fail();

				std::cin.clear();
			} while (streamError);
		}
		else{
			fileName = "Process finished.";
		}

		invoker.callCommand(commandIndex, fileName);

	} while (commandIndex != (static_cast<std::size_t>(commands::finisher)));

	delete pToFileCreator, pToDirectoryCreator, pToFileRemover;
	return 0;
}