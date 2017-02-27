#include "GameController.h"
#include "MeshRenderer.h"
#include "Terrain.h"
#include "Transform.h"

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::Start()
{
}

void GameController::Update()
{
}

void GameController::OnDelete()
{
}

XMFLOAT3 GameController::GridSquareFromTerrain(XMFLOAT3 _terrainLoc)
{
	GameObject* terrain = GameObject::FindFromTag("Terrain")[0];
	XMMATRIX mat = XMMatrixInverse(0, terrain->GetComponent<Transform>()->GetWorldMatrix()) * XMMatrixTranslation(_terrainLoc.x, _terrainLoc.y, _terrainLoc.z);
	XMVECTOR posVec = mat.r[3];
	XMFLOAT4 pos = terrain->GetComponent<MeshRenderer>()->GetMesh()->GetVertexData()[(int)posVec.m128_f32[0] * terrain->GetComponent<Terrain>()->GetHeight() + (int)posVec.m128_f32[2]].position;
	posVec = XMVectorSet(pos.x, pos.y, pos.z, pos.w);
	XMFLOAT3 terrPos = terrain->GetComponent<Transform>()->GetWorldPosition();
	posVec += XMVectorSet(terrPos.x, terrPos.y, terrPos.z, 1);
	return XMFLOAT3(posVec.m128_f32[0], posVec.m128_f32[1], posVec.m128_f32[2]);
}