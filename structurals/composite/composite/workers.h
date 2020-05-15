#ifndef WORKERS_H
#define WORKERS_H

#include "workerStructures.h"
#include <algorithm>
#include <vector>

using std::vector;

//Main hierarchy interface
class iWorker
{
private:
	virtual void incrementWorkersNumber() = 0;
	virtual void workerIDInitialization() = 0;

protected:
	workerData employeeData;

public:
	iWorker(int _salary, const std::string &_position, workerStatus _status);
	virtual ~iWorker() = default;
	virtual void assignJob(const std::string& _toDo) = 0;
	virtual void doTheJob() = 0;
	virtual void jobFinished() = 0;

	inline std::string getWorkerID(){
		return employeeData.workerID;
	}
};

//Composite
class manager : public iWorker, protected workersManagement {
private:
	inline virtual void incrementWorkersNumber() override {
		++managersNumber;
	}
	inline virtual void workerIDInitialization() override {
		employeeData.workerID = std::to_string(static_cast<short>(employeeData.contract) + managersNumber);
	}
	int selectCounterReference();
	bool isPositionInTaskUnitValid(const std::string& _positionInTaskUnit);
	static int managersNumber;

protected:
	int getNotBussyEmployeesNumber();

	job<vector<std::string>> assignedJob;

public:
	manager(int _salary, const std::string &_position) : iWorker(_salary, _position, workerStatus::manager) {
		workerIDInitialization();
		incrementWorkersNumber();
	}
	virtual ~manager();
	virtual void hireNewEmployee() final override;
	virtual void fireAnEmployee(std::string _workerID) final override;
	virtual void assignJob(const std::string& _positionInTaskUnit) override;
	virtual void doTheJob() override;
	virtual void jobFinished() override;
};

//Leaf / child
class worker final : public iWorker {
private:
	inline virtual void incrementWorkersNumber() override {
		++workersNumber;
	}
	inline virtual void workerIDInitialization() override {
		employeeData.workerID = std::to_string(static_cast<short>(employeeData.contract) + workersNumber);
	}
	static int workersNumber;

protected:
	job<std::string> assignedJob;

public:
	worker(int _salary, const std::string &_position, workerStatus _contract = workerStatus::employee) : iWorker(_salary, _position, _contract) {
		workerIDInitialization();
		incrementWorkersNumber();
	}
	virtual ~worker() = default;
	virtual void assignJob(const std::string& _toDo) override;
	virtual void doTheJob() override;
	virtual void jobFinished() override;

	bool isWorkerBussy() {
		return assignedJob.bussy;
	}
};
#endif // WORKERS_H