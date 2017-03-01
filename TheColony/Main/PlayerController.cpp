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
	if (GetAsyncKeyState(VK_LBUTTON))
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
		GameObject* outObj;
		bool ray = Collider::RayCastAll(outPos, outObj, nearPos, flDir);
		if (ray)
		{
			if (outObj == terrain)
			{
				GameObject::FindFromTag("GameController")[0]->GetComponent<GameController>()->PlaceBuilding(outPos);
			}
			else
			{
			}
		}
	}

	if (GetAsyncKeyState(VK_RSHIFT))
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
		GameObject* outObj;
		bool ray = Collider::RayCastAll(outPos, outObj, nearPos, flDir);
		if (ray)
		{
			if (outObj == terrain)
			{
				GameObject::FindFromTag("GameController")[0]->GetComponent<GameController>()->Predict(outPos);
			}
			else
			{
			}
		}
	}
}

void PlayerController::OnDelete()
{
}