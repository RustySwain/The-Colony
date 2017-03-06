#pragma once
#include "JobABC.h"
#include <DirectXMath.h>

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
	DirectX::XMFLOAT3 bufferSquare;
	bool needNewPath = true;

	static void FinishTask(vector<Task*>::iterator _iter, bool _squares);

public:
	Builder();
	~Builder();

	// Component
	void Start() override;
	void Update() override;
	void OnDelete() override;

	static void AddTask(GameObject* _job, Task::TASK_TYPE _taskType, unsigned int _maxWorkers, unsigned int _requiredWork);
	static void RemoveFromTasks(GameObject* _go);
	static void ShutDown();
};
