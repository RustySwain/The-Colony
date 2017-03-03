#pragma once
#include "JobABC.h"

class Builder : public JobABC
{
public:
	struct Task
	{
		enum TASK_TYPE { BUILD, GATHER };
		TASK_TYPE type;
		GameObject* job = nullptr;
		unsigned int maxWorkers;
		vector<Builder*> workers;
		unsigned int requiredWork;
		unsigned int workDone = 0;
	};

private:
	static vector<Task*> tasks;
	Task* currentTask = nullptr;
	float reachDistance = 1.0f;

	static void FinishTask(unsigned int _index);

public:
	Builder();
	~Builder();

	// Component
	void Start() override;
	void Update() override;
	void OnDelete() override;

	static void AddTask(GameObject* _job, Task::TASK_TYPE _taskType, unsigned int _maxWorkers);
};
