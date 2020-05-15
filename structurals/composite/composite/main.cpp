#include "header.h"

int main(){

	createTaskUnit(taskUnit);
	showTaskUnit(taskUnit);

	iWorker* pToWorker{nullptr};

	worker worker1 (100, "Programmer");
	worker worker2 (200, "Programmer");
	worker worker3 (300, "Programmer");

	manager mWorker1 (10000, "Programmers manager");

	for(int i = 0; i < 20; ++i){
		mWorker1.hireNewEmployee();
	}

	mWorker1.assignJob(std::to_string(1));
	mWorker1.doTheJob();
	mWorker1.jobFinished();
	mWorker1.fireAnEmployee("1008");

//Client is able to use both type (which are members of the same hierarchy) without knowledge
	pToWorker = &worker1;
	pToWorker->assignJob("123456789");
	pToWorker->doTheJob();
	
	pToWorker = &mWorker1;
	pToWorker->assignJob(std::to_string(8));
	pToWorker->doTheJob();

	return 0;
}