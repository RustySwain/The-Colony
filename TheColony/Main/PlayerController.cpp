#include "PlayerController.h"
#include "MeshRenderer.h"
#include "Terrain.h"

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
}

void PlayerController::OnDelete()
{
}

XMFLOAT3 PlayerController::GridSquareFromTerrain(XMFLOAT3 _terrainLoc)
{
	GameObject* terrain = GameObject::FindFromTag("Terrain")[0];
	XMFLOAT4 pos = terrain->GetComponent<MeshRenderer>()->GetMesh()->GetVertexData()[(int)_terrainLoc.z * terrain->GetComponent<Terrain>()->GetWidth() + (int)_terrainLoc.x].position;
	return XMFLOAT3(pos.x, pos.y, pos.z);
}