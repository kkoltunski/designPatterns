#ifndef WORKERSTRUCTURES_H
#define WORKERSTRUCTURES_H

#include <iostream>
#include <string>
#include <list>

class iWorker;
enum class workerStatus : short { employee = 1000, b2b = 2000, manager = 3000 };

/*This is abstract struct no class because hierarchy
could be developed about new parent type (e.g. director)
and then manager will be child of director - different types would be allocated in memory*/
struct workersManagement {
private:
	virtual void hireNewEmployee() = 0;
	virtual void fireAnEmployee(std::string _workerID) = 0;

protected:
	std::list<iWorker*> subordinateEmployees;
};

struct workerData {
public:
	int salary;
	workerStatus contract;
	std::string position;
	std::string workerID;
};

template<typename T>
struct job{
public:
	T jobReference;
	uint8_t progress;
	bool bussy{false};
};
#endif // WORKERSTRUCTURES_H