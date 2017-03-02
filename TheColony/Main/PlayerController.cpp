#include "PlayerController.h"
#include "MeshRenderer.h"
#include "Terrain.h"
#include "Collider.h"
#include "Camera.h"
#include "GameController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Start()
{
}

void PlayerController::Update()
{
	if (GetAsyncKeyState('R') & 0x1)
	{
		rotation++;
		rotation %= 4;
	}

	if (GetAsyncKeyState('0'))
		buildingIndex = -1;
	if (GetAsyncKeyState('1'))
		buildingIndex = 0;
	/*if (GetAsyncKeyState('2'))
		buildingIndex = 1;*/

	if (GetAsyncKeyState(VK_LBUTTON) && buildingIndex != -1)
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		XMFLOAT3 mouseScreen((float)mousePos.x, (float)mousePos.y, 0);
		XMFLOAT3 nearPos = Camera::mainCam->ScreenToWorldSpace(mouseScreen);
		mouseScreen.z = Camera::mainCam->GetFarPlane();
		XMFLOAT3 farPos = Camera::mainCam->ScreenToWorldSpace(mouseScreen);
		XMVECTOR nearVec = XMVectorSet(nearPos.x, nearPos.y, nearPos.z, 1);
		XMVECTOR farVec = XMVectorSet(farPos.x, farPos.y, farPos.z, 1);
		XMVECTOR vecDir = XMVector3Normalize(farVec - nearVec);
		XMFLOAT3 flDir(vecDir.m128_f32[0], vecDir.m128_f32[1], vecDir.m128_f32[2]);
		XMFLOAT3 outPos;
		GameObject* terrain = GameObject::FindFromTag("Terrain")[0];
		bool ray = terrain->GetComponent<Collider>()->RayCast(outPos, nearPos, flDir);
		if (ray)
		{
			GameObject::FindFromTag("GameController")[0]->GetComponent<GameController>()->PlaceBuilding(outPos, rotation, buildingIndex);
		}
	}

	GameObject::FindFromTag("GameController")[0]->GetComponent<GameController>()->ClearPrediction();
	if (buildingIndex != -1)
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		XMFLOAT3 mouseScreen((float)mousePos.x, (float)mousePos.y, 0);
		XMFLOAT3 nearPos = Camera::mainCam->ScreenToWorldSpace(mouseScreen);
		mouseScreen.z = Camera::mainCam->GetFarPlane();
		XMFLOAT3 farPos = Camera::mainCam->ScreenToWorldSpace(mouseScreen);
		XMVECTOR nearVec = XMVectorSet(nearPos.x, nearPos.y, nearPos.z, 1);
		XMVECTOR farVec = XMVectorSet(farPos.x, farPos.y, farPos.z, 1);
		XMVECTOR vecDir = XMVector3Normalize(farVec - nearVec);
		XMFLOAT3 flDir(vecDir.m128_f32[0], vecDir.m128_f32[1], vecDir.m128_f32[2]);
		XMFLOAT3 outPos;
		GameObject* terrain = GameObject::FindFromTag("Terrain")[0];
		bool ray = terrain->GetComponent<Collider>()->RayCast(outPos, nearPos, flDir);
		if (ray)
		{
			GameObject::FindFromTag("GameController")[0]->GetComponent<GameController>()->Predict(outPos, rotation, buildingIndex);
		}
	}
}

void PlayerController::OnDelete()
{
}