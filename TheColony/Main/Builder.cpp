#include "Builder.h"
#include <DirectXMath.h>
#include "Transform.h"

vector<Builder::Task*> Builder::tasks;

void Builder::FinishTask(unsigned int _index)
{
	// Remove all workers from the task
	while (tasks[_index]->workers.size())
	{
		tasks[_index]->workers[0]->currentTask = nullptr;
		tasks[_index]->workers.erase(tasks[_index]->workers.begin());
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
		}
		// Otherwise, just wander around until there's a job available
		else
		{
			// Wander code
			return;
		}
	}

	// TODO: If my job site needs more resources, go get them

	// If I need to travel to my job, do it
	XMFLOAT3 myPosition = gameObject->GetComponent<Transform>()->GetWorldPosition();
	XMFLOAT3 jobPosition = currentTask->job->GetComponent<Transform>()->GetWorldPosition();
	XMFLOAT3 toJob(jobPosition.x - myPosition.x, jobPosition.y - myPosition.y, jobPosition.z - myPosition.z);
	float distance = sqrt(toJob.x * toJob.x + toJob.z * toJob.z);
	if (distance > reachDistance)
	{
		// request path to job
		return;
	}

	// I'm at my job. Do work
	currentTask->workDone++;

	// If the job is finished, remove it from the queue
	if (currentTask->requiredWork <= currentTask->workDone)
	{
		FinishTask((unsigned int)(find(tasks.begin(), tasks.end(), currentTask) - tasks.begin()));
	}
}

void Builder::OnDelete()
{
}

void Builder::AddTask(GameObject* _job, Task::TASK_TYPE _taskType, unsigned int _maxWorkers)
{
	Task* task = new Task();
	task->type = _taskType;
	task->job = _job;
	task->maxWorkers = _maxWorkers;
	tasks.push_back(task);
}