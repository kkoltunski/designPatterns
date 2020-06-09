#include "streamStrategy.h"

void filestreamToUpper::operation(boostedFstream* const _streamPtr){
	workSpace = _streamPtr->getFileContent();

	for(auto &character : workSpace){
		character = std::toupper(character);
	}
	
	_streamPtr->putContentToFile(workSpace);
}

void filestreamToLower::operation(boostedFstream* const _streamPtr) {
	workSpace = _streamPtr->getFileContent();

	for (auto& character : workSpace) {
		character = std::tolower(character);
	}

	_streamPtr->putContentToFile(workSpace);
}

bool filestreamSeparator::areIndexesInRange(char _actualChar, char _nextChar){
	short bottomASCIIRange = 33;
	short upperASCIIRange = 125;
	bool result{ true };

	if ((_actualChar < bottomASCIIRange || _actualChar > upperASCIIRange) && (_actualChar != separator)) {
		if((_nextChar < bottomASCIIRange || _nextChar > upperASCIIRange) && (_nextChar != separator)){
			result = false;
		}
	}

	return result;
}

void filestreamSeparator::operation(boostedFstream* const _streamPtr) {
	workSpace = _streamPtr->getFileContent();

	for(int i = 0; i < workSpace.size(); ++i){
		int nextIndex = i + 1;

		if(nextIndex <= workSpace.size()){
			if(areIndexesInRange(workSpace[i], workSpace[nextIndex])){
				std::string::iterator placeToInsert = (workSpace.begin() + nextIndex);
				workSpace.insert(placeToInsert, separator);
				++i;
			}
		}
		else{
			break;
		}
	}

	_streamPtr->putContentToFile(workSpace);
}