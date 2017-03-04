#include "VillagerController.h"
#include "Transform.h"
#include "Time.h"
#include <string>
#include "Debug.h"
#include <Windows.h>
#include "Animator.h"
#include <random>
#include "House.h"
#include "Terrain.h"
#include "Farm.h"

#define MAX_INVENTORY 200

void VillagerController::Start()
{
}

void VillagerController::Update()
{
	int hours = GameObject::FindFromTag("GameController")[0]->GetComponent<GameController>()->GetGameTime().hours;
	if (hours >= 6 && hours <= 18)
	{
		if (age > 14)
		{
			if (GetAsyncKeyState('M') & 0x1)
			{
				if (house)
					RequestPath(gameObject->GetComponent<Transform>()->GetWorldPosition(), house->GetComponent<House>()->GetFrontDoor());
				else
					Wander();
			}

			if (HOME == step)
			{
				RequestPath(gameObject->GetComponent<Transform>()->GetWorldPosition(), FindJob()->GetComponent<Farm>()->GetFrontDoor());
			}
			else if (TRAVELING == step)
			{
				Move();

				if (pathCount == pathToWalk.size())
				{
					gameObject->GetComponent<Animator>()->Play("Idle");
					pathCount = 0;
					pathToWalk.clear();
					step = HOME;
				}
			}
			else if (WORKING == step)
			{
				if (isWorking)
				{
					// TODO: do job
					if ((int)inventory.size() == MAX_INVENTORY)
					{
					}
				}
				else
					RequestPath(gameObject->GetComponent<Transform>()->GetWorldPosition(), house->GetComponent<House>()->GetFrontDoor());
			}
		}
		else
		{
			
		}
	}
	else
	{
		Wander();
		Move();
	}

	if (!moveFlag)
		moveFlag = true;
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
}

void VillagerController::Notify()
{
	if(TRAVELING == step)
		recalculatePath = true;
}

void VillagerController::Wander()
{
	if(pathToWalk.size() == 0)
	{
		int randX = rand() % (GameObject::FindFromTag("Terrain")[0]->GetComponent<Terrain>()->GetWidth() - 4) + 2;
		int randZ = rand() % (GameObject::FindFromTag("Terrain")[0]->GetComponent<Terrain>()->GetHeight() - 4) + 2;
		RequestPath(gameObject->GetComponent<Transform>()->GetWorldPosition(), XMFLOAT3((float)randX, 2.4f, (float)randZ));
	}
}

GameObject * VillagerController::FindJob()
{
	return nullptr;
}

void VillagerController::Move()
{
	if (moveFlag && pathToWalk.size() > 0)
	{
		if (gameObject->GetComponent<Animator>()->CurrAnimation() != "Run")
			gameObject->GetComponent<Animator>()->Play("Run");

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
		if (distToTile < 0.1f)
		{
			++pathCount;
			if (pathCount < pathToWalk.size())
			{
				XMFLOAT3 nextPosition = pathToWalk[pathCount];
				gameObject->GetComponent<Transform>()->LookAt(nextPosition);
				if (recalculatePath)
				{
					RequestPath(currPosition, pathToWalk[pathToWalk.size() - 1]);
					recalculatePath = false;
				}
			}
		}
	}
}
