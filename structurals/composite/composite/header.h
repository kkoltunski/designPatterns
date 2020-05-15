#ifndef HEADER_H
#define HEADER_H

#include <initializer_list>
#include "workers.h"

using std::string;

//tickets numbers
vector<vector<string>> taskUnit;

//Tickets number generator - just for data to operate
void createTaskUnit(vector<vector<string>> &_vectorRef){
	std::initializer_list<string> initList{ "123", "456", "789", "101", "112", "113", "245", "982", "999", "444" };
	vector<string> auxiliaryVector{ initList };

	for(int i = 0; i < 10; ++i){
		_vectorRef.push_back(auxiliaryVector);

		for(int x = 0; x < 10; ++x){
			int valueFromString = std::stoi(auxiliaryVector[x]);
			valueFromString += 10;
			auxiliaryVector[x] = std::to_string(valueFromString);
		}
	}
}

void showTaskUnit(vector<vector<string>>& _vectorRef){
	for(int i = 0; i < 10; ++i){
		for(int x = 0; x < 10; ++x){
			std::cout << _vectorRef[i][x] << ",";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
#endif // HEADER_H