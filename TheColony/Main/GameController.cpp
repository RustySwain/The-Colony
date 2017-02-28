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
	smallHouses.Start();
	smallHouses.AddComponent<Transform>();
	smallHouses.AddComponent<MeshRenderer>()->LoadFromObj("../Assets/Buildings/SmallHousePlaceHolder.obj");
	smallHouses.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/bark.dds");
}

void GameController::Update()
{
	static bool updated = false;
	if (!updated)
		smallHouses.GetComponent<MeshRenderer>()->RemoveInstance(-1);
	smallHouses.Update();
}

void GameController::OnDelete()
{
	smallHouses.OnDelete();
}

XMFLOAT3 GameController::GridSquareFromTerrain(XMFLOAT3 _terrainLoc)
{
	GameObject* terrain = GameObject::FindFromTag("Terrain")[0];
	XMFLOAT4 pos = terrain->GetComponent<MeshRenderer>()->GetMesh()->GetVertexData()[(int)_terrainLoc.x * terrain->GetComponent<Terrain>()->GetHeight() + (int)_terrainLoc.z].position;
	return XMFLOAT3(pos.x, pos.y, pos.z);
}

bool GameController::PlaceBuilding(XMFLOAT3 _gridSquare)
{
	XMFLOAT3 terrPos = GridSquareFromTerrain(_gridSquare);
	XMMATRIX translation = XMMatrixTranslation(terrPos.x, terrPos.y, terrPos.z);
	smallHouses.GetComponent<MeshRenderer>()->AddInstance(translation, (int)_gridSquare.x * GameObject::FindFromTag("Terrain")[0]->GetComponent<Terrain>()->GetHeight() + (int)_gridSquare.z);
	return true;
}