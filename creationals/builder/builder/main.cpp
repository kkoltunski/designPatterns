#include "header.h"

int main(){

	whiteSedanBuilder builder;
	carInfoDirector director(&builder);
	std::shared_ptr<carInformations> product = director.construct();

	return 0;
}