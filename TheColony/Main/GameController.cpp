#include "GameController.h"
#include "MeshRenderer.h"
#include "Terrain.h"
#include "Transform.h"
#include "Collider.h"

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::Start()
{
	smallHouse.instances.Start();
	smallHouse.instances.AddComponent<Transform>();
	smallHouse.instances.AddComponent<MeshRenderer>()->LoadFromObj("../Assets/Buildings/SmallHousePlaceHolder.obj");
	smallHouse.instances.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/bark.dds");
}

void GameController::Update()
{
	static bool updated = false;
	if (!updated)
	{
		updated = true;
		smallHouse.instances.GetComponent<MeshRenderer>()->RemoveInstance(-1);
	}
	smallHouse.instances.Update();
	for (unsigned int i = 0; i < smallHouse.colliders.size(); i++)
		smallHouse.colliders[i].Update();
}

void GameController::OnDelete()
{
	smallHouse.instances.OnDelete();
	for (unsigned int i = 0; i < smallHouse.colliders.size(); i++)
		smallHouse.colliders[i].OnDelete();
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
	smallHouse.instances.GetComponent<MeshRenderer>()->AddInstance(translation, (int)_gridSquare.x * GameObject::FindFromTag("Terrain")[0]->GetComponent<Terrain>()->GetHeight() + (int)_gridSquare.z);

	GameObject& nuCollider = GameObject();
	nuCollider.Start();
	nuCollider.AddComponent<Transform>()->SetLocalPosition(terrPos.x, terrPos.y, terrPos.z);
	nuCollider.AddComponent<Collider>()->SetMesh(smallHouse.instances.GetComponent<MeshRenderer>()->GetMesh());
	smallHouse.colliders.push_back(nuCollider);
	return true;
}