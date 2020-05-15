#include "workers.h"

int worker::workersNumber{ 0 };
int manager::managersNumber{ 0 };

extern vector<vector<std::string>> taskUnit;

iWorker::iWorker(int _salary, std::string _position, workerStatus _status) {
	employeeData.salary = _salary;
	employeeData.position = _position;
	employeeData.contract = _status;
}

manager::~manager(){
	std::for_each(subordinateEmployees.begin(), subordinateEmployees.end(), [](iWorker *pToWorker) {delete pToWorker; });
}

void manager::hireNewEmployee(){
	//...any interface to modify workers contract
	subordinateEmployees.push_back(new worker(2000, "C/C++ Programmer", workerStatus::employee));
}

void manager::fireAnEmployee(std::string _workerID){
	int indexCounter{ 0 };

	for(auto employee = subordinateEmployees.begin(); employee != subordinateEmployees.end(); employee++, indexCounter++){
		if((*employee)->getWorkerID() == _workerID){
			delete* employee;
			subordinateEmployees.erase(employee);
			break;
		}
		else if (indexCounter == subordinateEmployees.size()){
			std::cout << "Worker " << _workerID << " is not found in this team." << std::endl;
		}
	}
}

bool manager::isPositionInTaskUnitValid(const std::string& _positionInTaskUnit){
	return ((_positionInTaskUnit[0] >= '0') && (_positionInTaskUnit[0] <= '9'));
}

void manager::assignJob(const std::string& _positionInTaskUnit) {
	//this function is a makeshift communication interface with something superior
	if((isPositionInTaskUnitValid(_positionInTaskUnit) && !(assignedJob.bussy))){
		int taskUnitIndex = (_positionInTaskUnit[0] - '0');
		assignedJob.jobReference = taskUnit[taskUnitIndex];
		assignedJob.bussy = true;
	}
	else{
		std::cout << "Wrong task unit index." << std::endl;
	}
}

int manager::getNotBussyEmployeesNumber(){
	int notBussyEmployees{ 0 };

	for (auto employee : subordinateEmployees) {
		if (!(static_cast<worker*>(employee)->isWorkerBussy())) {
			notBussyEmployees++;
		}
	}

	return notBussyEmployees;
}

int manager::selectCounterReference(){
	int notBussySubordinateEmployeesNumber = getNotBussyEmployeesNumber();
	int assignedJobUnitSize = assignedJob.jobReference.size();

	return (notBussySubordinateEmployeesNumber > assignedJobUnitSize ? assignedJobUnitSize : notBussySubordinateEmployeesNumber);
}

void manager::doTheJob(){
	if(assignedJob.jobReference.size() != 0){
		int maximumJobsToAssign = (selectCounterReference() - 1);
		int jobsIndex{ 0 };

		/*It doesnt work in C++11 (is able since C++17)
		for(auto employee = subordinateEmployees.begin(), int i = 0; i < jobsToAssign; ++i, ++employe){
		}
		Thats why i had to create controled "range-based for" bellow.*/

		for (auto employee : subordinateEmployees) {
			if (!(static_cast<worker*>(employee)->isWorkerBussy())) {
				static_cast<worker*>(employee)->assignJob(assignedJob.jobReference[jobsIndex]);
				static_cast<worker*>(employee)->doTheJob();
			}

			if (jobsIndex < maximumJobsToAssign) {
				jobsIndex++;
			}
			else {
				break;
			}
		}
	}
	else{
		std::cout << "Worker " << employeeData.workerID << " has no job to do or is already bussy." << std::endl;
	}
}

void manager::jobFinished() {
	if(assignedJob.bussy){
		assignedJob.jobReference.clear();
		assignedJob.bussy = false;
	}
}

void worker::assignJob(const std::string& _toDo){
	if(!assignedJob.bussy){
		assignedJob.jobReference = _toDo;
		assignedJob.bussy = true;
		//doTheJob();
	}
}

void worker::doTheJob() {
	if(assignedJob.jobReference.size() != 0){
		std::cout << "Worker " << employeeData.workerID << " is assigned to " << assignedJob.jobReference << " job." << std::endl;
		jobFinished();
	}
	else{
		std::cout << "Worker " << employeeData.workerID << " has no job to do or is already bussy" << std::endl;
	}
}

void worker::jobFinished(){
	if (assignedJob.bussy) {
		assignedJob.jobReference = "";
		assignedJob.bussy = false;
	}
}