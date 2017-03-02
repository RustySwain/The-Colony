#include "VillagerController.h"
#include "Transform.h"
#include "Time.h"
#include <string>
#include "Debug.h"
#include <Windows.h>
#include "Animator.h"
#include <random>

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
	if(house == nullptr)
	{
		vector<GameObject*> houses = GameObject::FindFromTag("House");
		if (houses.size() > 0)
		{
			house = houses[0];
		}
	}

	float hours = GameObject::FindFromTag("GameController")[0]->GetComponent<GameController>()->GetHours();
	if (hours >= 0)
	{
		if (age > 14)
		{
			if (HOME == step)
			{
				if (GetAsyncKeyState('N') & 0x1)
				{
					float randX = float(rand() % 32 - 1);
					float randZ = float(rand() % 32 - 1);
					gameObject->GetComponent<Transform>()->SetLocalPosition(randX, 2.4f, randZ);
				}

				if (GetAsyncKeyState('M') & 0x1)
					RequestPath(gameObject->GetComponent<Transform>()->GetWorldPosition(), XMFLOAT3(10, 2.4f, 25));
			}
			else if (TRAVELING == step)
			{
				if (moveFlag)
				{
					XMFLOAT3 newPosition = pathToWalk[pathCount];
					gameObject->GetComponent<Transform>()->LookAt(newPosition);
					XMFLOAT3 currPosition = gameObject->GetComponent<Transform>()->GetWorldPosition();
					XMVECTOR newPosVec = XMVectorSet(newPosition.x, newPosition.y, newPosition.z, 1);
					XMVECTOR currPosVec = XMVectorSet(currPosition.x, currPosition.y, currPosition.z, 1);
					newPosVec -= currPosVec;
					newPosVec = XMVector3Normalize(newPosVec);
					newPosVec *= Time::Delta() * speed;
					newPosVec += currPosVec;
					gameObject->GetComponent<Transform>()->SetLocalPosition(newPosVec.m128_f32[0], newPosVec.m128_f32[1], newPosVec.m128_f32[2]);

					float distToTile = sqrt(pow(pathToWalk[pathCount].x - currPosition.x, 2) + pow(pathToWalk[pathCount].z - currPosition.z, 2));
					if (distToTile <= 0.05f && ++pathCount < pathToWalk.size())
					{
						XMFLOAT3 nextPosition = pathToWalk[pathCount];
						gameObject->GetComponent<Transform>()->LookAt(nextPosition);
						if(recalculatePath)
						{
							RequestPath(currPosition, XMFLOAT3(10, 2.4f, 25));
							recalculatePath = false;
						}
					}

					if (pathCount == pathToWalk.size())
					{
						gameObject->GetComponent<Animator>()->Play("Idle");
						pathCount = 0;
						pathToWalk.clear();

						if (hours >= 0)
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
			}
			else if (WORKING == step)
			{
				if (isWorking)
				{
					// TODO: do job
					if ((int)inventory.size() == 200)
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
	reverse(path.begin(), path.end());
	pathCount = 0;
	pathToWalk = path;
	step = TRAVELING;
	moveFlag = true;
	gameObject->GetComponent<Animator>()->Play("Run");
}

void VillagerController::Notify()
{
	if(TRAVELING == step)
	{
		recalculatePath = true;
	}
}

GameObject * VillagerController::FindJob()
{
	return nullptr;
}