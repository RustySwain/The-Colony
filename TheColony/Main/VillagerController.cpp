#include "VillagerController.h"
#include "Transform.h"
#include "Time.h"

VillagerController::VillagerController()
{
}

VillagerController::~VillagerController()
{
}

void VillagerController::Start()
{
}

void VillagerController::Update()
{
	float hours = GameObject::FindFromTag("GameController")[0]->GetComponent<GameController>()->GetHours();
	if(hours >= 6)
	{
		if(age > 14)
		{
			if(HOME == step)
			{
				//RequestPath(gameObject->GetComponent<Transform>()->GetWorldPosition(), FindJob()->GetComponent<Transform>()->GetWorldPosition());
				RequestPath(gameObject->GetComponent<Transform>()->GetWorldPosition(), XMFLOAT3(-2, 2.2f, 3));
			}
			else if(TRAVELING == step)
			{
				XMFLOAT3 newPosition = pathToWalk[pathCount];
				newPosition.x *= Time::Delta();
				newPosition.y *= Time::Delta();
				newPosition.z *= Time::Delta();
				gameObject->GetComponent<Transform>()->TranslatePre(newPosition);
				pathCount++;
				if(pathCount == pathToWalk.size())
				{
					pathCount = 0;
					pathToWalk.clear();

					if(hours >= 17)
					{
						step = HOME;
					}
					else
					{
						step = WORKING;
						isWorking = true;
					}
					
				}
			}
			else if(WORKING == step)
			{
				if(isWorking)
				{
					// TODO: do job
					if((int)inventory.size() == 200)
					{
						
					}
				}
				else
					RequestPath(gameObject->GetComponent<Transform>()->GetWorldPosition(), house->GetComponent<Transform>()->GetWorldPosition());
			}
		}
		else
		{
			
		}
	}
}

void VillagerController::OnDelete()
{
}

void VillagerController::RequestPath(XMFLOAT3 _from, XMFLOAT3 _to)
{
	vector<XMFLOAT3> path = GameObject::FindFromTag("GameController")[0]->GetComponent<GameController>()->AStar(_from, _to);
	step = TRAVELING;
}

GameObject * VillagerController::FindJob()
{
	return nullptr;
}
