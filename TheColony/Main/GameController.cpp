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
	XMFLOAT4 pos = terrain->GetComponent<MeshRenderer>()->GetMesh()->GetVertexData()[(int)posVec.m128_f32[2] * terrain->GetComponent<Terrain>()->GetWidth() + (int)posVec.m128_f32[0]].position;
	return XMFLOAT3(pos.x, pos.y, pos.z);
}