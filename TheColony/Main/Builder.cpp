#include "Builder.h"
#include <DirectXMath.h>
#include "Transform.h"
#include "VillagerController.h"
#include "House.h"
#include "Windows.h"

vector<Builder::Task*> Builder::tasks;

void Builder::FinishTask(vector<Task*>::iterator _iter)
{
	// Remove all workers from the task
	while ((*_iter)->workers.size())
	{
		(*_iter)->workers[0]->currentTask = nullptr;
		(*_iter)->workers.erase((*_iter)->workers.begin());
	}

	if ((*_iter)->type == Task::BUILD)
	{
	}
	// Remove the task from the queue
	delete tasks[0];
	tasks.erase(tasks.begin());
}

Builder::Builder()
{
}

Builder::~Builder()
{
}

void Builder::Start()
{
}

void Builder::Update()
{
	// If I don't have a job
	if (currentTask == nullptr)
	{
		if (GetAsyncKeyState('Y'))
			int s = 0;
		// Find a job with enough room for me
		int taskIndex = -1;
		for (unsigned int i = 0; i < tasks.size(); i++)
		{
			if (tasks[i]->workers.size() < tasks[i]->maxWorkers)
			{
				taskIndex = i;
			}
		}

		// If I found a job, take the job
		if (taskIndex != -1)
		{
			tasks[taskIndex]->workers.push_back(this);
			currentTask = tasks[taskIndex];
			bufferSquare = currentTask->job->GetComponent<House>()->GetRandomBufferSquare();
		}
		// Otherwise, just wander around until there's a job available
		else
		{
			gameObject->GetComponent<VillagerController>()->Wander();
			return;
		}
	}

	// TODO: If my job site needs more resources, go get them

	// If I need to travel to my job, do it
	XMFLOAT3 myPosition = gameObject->GetComponent<Transform>()->GetWorldPosition();
	XMFLOAT3 toJob(bufferSquare.x - myPosition.x, bufferSquare.y - myPosition.y, bufferSquare.z - myPosition.z);
	float distance = sqrt(toJob.x * toJob.x + toJob.z * toJob.z);
	if (distance > reachDistance)
	{
		// request path to job
		if (needNewPath)
		{
			gameObject->GetComponent<VillagerController>()->RequestPath(gameObject->GetComponent<Transform>()->GetWorldPosition(), bufferSquare);
			needNewPath = false;
		}
		return;
	}

	// I'm at my job. Do work
	currentTask->workDone++;

	// If the job is finished, remove it from the queue
	if (currentTask->requiredWork <= currentTask->workDone)
	{
		FinishTask(find(tasks.begin(), tasks.end(), currentTask));
		needNewPath = true;
	}
}

void Builder::OnDelete()
{
	if (currentTask)
		currentTask->workers.erase(find(currentTask->workers.begin(), currentTask->workers.end(), this));
}

void Builder::AddTask(GameObject* _job, Task::TASK_TYPE _taskType, unsigned int _maxWorkers, unsigned int _requiredWork)
{
	Task* task = new Task();
	task->type = _taskType;
	task->job = _job;
	task->maxWorkers = _maxWorkers;
	task->requiredWork = _requiredWork;
	tasks.push_back(task);
}

void Builder::ShutDown()
{
	while (tasks.size())
		FinishTask(tasks.begin());
}