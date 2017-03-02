#include "VillagerController.h"
#include "Transform.h"
#include "Time.h"
#include <string>
#include "Debug.h"
#include <Windows.h>

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
	totalTime += Time::Delta();

	float hours = GameObject::FindFromTag("GameController")[0]->GetComponent<GameController>()->GetHours();
	if (hours >= 0)
	{
		if (age > 14)
		{
			if (HOME == step)
			{
				if(GetAsyncKeyState('T') & 0x1)
					RequestPath(gameObject->GetComponent<Transform>()->GetWorldPosition(), XMFLOAT3(10, 2.4f, 25));
			}
			else if (TRAVELING == step)
			{
				if (moveFlag && totalTime >= 7.0f)
				{
					XMFLOAT3 newPosition = pathToWalk[pathCount];
					XMFLOAT3 currPosition = gameObject->GetComponent<Transform>()->GetWorldPosition();
					XMVECTOR newPosVec = XMVectorSet(newPosition.x, newPosition.y, newPosition.z, 1);
					XMVECTOR currPosVec = XMVectorSet(currPosition.x, currPosition.y, currPosition.z, 1);
					newPosVec -= currPosVec;
					newPosVec = XMVector3Normalize(newPosVec);
					newPosVec *= Time::Delta() * 2.3f;
					string pos = to_string(newPosVec.m128_f32[0]);
					pos += ", ";
					pos += to_string(newPosVec.m128_f32[1]);
					pos += ", ";
					pos += to_string(newPosVec.m128_f32[2]);
					Debug::Log(pos, 0);
					newPosVec += currPosVec;
					gameObject->GetComponent<Transform>()->SetLocalPosition(newPosVec.m128_f32[0], newPosVec.m128_f32[1], newPosVec.m128_f32[2]);
					
					float distToTile = sqrt(pow(pathToWalk[pathCount].x - currPosition.x, 2) + pow(pathToWalk[pathCount].z - currPosition.z, 2));
					if (distToTile <= 0.05f)
					{
						pathCount++;

						XMFLOAT3 nextPosition = pathToWalk[pathCount];
						XMVECTOR nextPosVec = XMVectorSet(newPosition.x, nextPosition.y, nextPosition.z, 1);
						nextPosVec = XMVector3Normalize(nextPosVec);

						XMMATRIX tempMat = XMMatrixIdentity();
						gameObject->GetComponent<Transform>()->SetLocalMatrix(tempMat);
						gameObject->GetComponent<Transform>()->SetLocalPosition(newPosVec.m128_f32[0], newPosVec.m128_f32[1], newPosVec.m128_f32[2]);

						//float angle = acos(nextPosVec);
						//gameObject->GetComponent<Transform>()->RotateYPre(angle);

						
					}

					if (pathCount == pathToWalk.size())
					{
						pathCount = 0;
						pathToWalk.clear();

						if (hours >= 17)
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

	if(!moveFlag)
		moveFlag = true;
}

void VillagerController::OnDelete()
{
}

void VillagerController::RequestPath(XMFLOAT3 _from, XMFLOAT3 _to)
{
	vector<XMFLOAT3> path = GameObject::FindFromTag("GameController")[0]->GetComponent<GameController>()->AStar(_from, _to);
	reverse(path.begin(), path.end());
	pathToWalk = path;
	step = TRAVELING;
}

GameObject * VillagerController::FindJob()
{
	return nullptr;
}
