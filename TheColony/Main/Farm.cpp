#include "Farm.h"

void Farm::Start()
{
}

void Farm::Update()
{
}

void Farm::OnDelete()
{
}

bool Farm::AddWorker(GameObject * _worker)
{
	if((unsigned int)currWorkers.size() < maxWorkers)
	{
		currWorkers.push_back(_worker);
		return true;
	}

	return false;
}
