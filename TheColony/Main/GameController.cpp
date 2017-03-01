#include "GameController.h"
#include "MeshRenderer.h"
#include "Terrain.h"
#include "Transform.h"
#include "Collider.h"
#include "Time.h"
#include "fstream"
#include "sstream"
#include "PathSearch.h"
#include "BuildingPredictor.h"

bool GameController::LoadOccupiedSquares(const char* _path, vector<XMFLOAT2>& _vec)
{
	ifstream reader(_path, ios_base::in);
	if (reader.is_open())
	{
		while (!reader.eof())
		{
			char buffer[256];
			reader.getline(buffer, 256);
			stringstream sstream(buffer);
			XMFLOAT2 fl2;
			sstream >> fl2.y >> fl2.x;
			_vec.push_back(fl2);
		}
		return true;
	}
	return false;
}

GameController::GameController() : terrainWidth(0), terrainHeight(0)
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
	smallHouse.collisionMesh = new Mesh();
	smallHouse.collisionMesh->LoadFromObj("../Assets/Buildings/SmallHouseCollision.obj");
	LoadOccupiedSquares("../Assets/Buildings/SmallHouse.building", smallHouse.occupiedSquares);

	buildingPredictor.Start();
	buildingPredictor.AddComponent<Transform>();
	buildingPredictor.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/White.dds");
	buildingPredictor.AddComponent<BuildingPredictor>();
}

void GameController::Update()
{
	gameTime += Time::Delta();
	hours += gameTime;
	if (hours >= 86400)
		hours = 0;

	smallHouse.instances.Update();
	for (unsigned int i = 0; i < smallHouse.colliders.size(); i++)
		smallHouse.colliders[i].Update();
	static bool updated = false;
	if (!updated)
	{
		updated = true;
		smallHouse.instances.GetComponent<MeshRenderer>()->RemoveInstance(-1);
		GameObject* terrain = GameObject::FindFromTag("Terrain")[0];
		terrainWidth = terrain->GetComponent<Terrain>()->GetWidth();
		terrainHeight = terrain->GetComponent<Terrain>()->GetHeight();
		gridCost = new float*[terrainHeight];
		for (unsigned int i = 0; i < terrainHeight; i++)
		{
			gridCost[i] = new float[terrainWidth];
			for (unsigned int j = 0; j < terrainWidth; j++)
			{
				gridCost[i][j] = 1;
			}
		}
	}

	buildingPredictor.Update();
}

void GameController::OnDelete()
{
	smallHouse.instances.OnDelete();
	for (unsigned int i = 0; i < smallHouse.colliders.size(); i++)
		smallHouse.colliders[i].OnDelete();
	delete smallHouse.collisionMesh;

	for (unsigned int i = 0; i < terrainHeight; i++)
		delete[] gridCost[i];
	delete[] gridCost;
	buildingPredictor.OnDelete();
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

	for (unsigned int i = 0; i < smallHouse.occupiedSquares.size(); i++)
	{
		int x = (unsigned int)smallHouse.occupiedSquares[i].x;
		int y = (unsigned int)smallHouse.occupiedSquares[i].y;
		if ((unsigned int)(x + (int)terrPos.x) >= terrainWidth - 1 || (unsigned int)(y + (int)terrPos.z) >= terrainHeight - 1 || (y + (int)terrPos.z) < 0 || (x + (int)terrPos.x) < 0) return false;
		if (gridCost[y + (int)terrPos.z][x + (int)terrPos.x] != 1) return false;
	}

	for (unsigned int i = 0; i < smallHouse.occupiedSquares.size(); i++)
	{
		unsigned int x = (unsigned int)smallHouse.occupiedSquares[i].x;
		unsigned int y = (unsigned int)smallHouse.occupiedSquares[i].y;
		if ((unsigned int)(x + (int)terrPos.x) >= terrainWidth - 1 || (unsigned int)(y + (int)terrPos.z) >= terrainHeight - 1 || (y + (int)terrPos.z) < 0 || (x + (int)terrPos.x) < 0) return false;
		gridCost[y + (int)terrPos.z][x + (int)terrPos.x] = 0;
	}

	XMMATRIX translation = XMMatrixTranslation(terrPos.x, terrPos.y, terrPos.z);
	smallHouse.instances.GetComponent<MeshRenderer>()->AddInstance(translation, (int)_gridSquare.x * GameObject::FindFromTag("Terrain")[0]->GetComponent<Terrain>()->GetHeight() + (int)_gridSquare.z);

	GameObject& nuCollider = GameObject();
	nuCollider.Start();
	nuCollider.AddComponent<Transform>()->SetLocalPosition(terrPos.x, terrPos.y, terrPos.z);
	nuCollider.AddComponent<Collider>()->SetMesh(smallHouse.collisionMesh);
	smallHouse.colliders.push_back(nuCollider);

	return true;
}

bool GameController::Predict(XMFLOAT3 _gridSquare)
{
	buildingPredictor.GetComponent<BuildingPredictor>()->Clear();

	XMFLOAT3 terrPos = GridSquareFromTerrain(_gridSquare);

	for (unsigned int i = 0; i < smallHouse.occupiedSquares.size(); i++)
	{
		int x = (unsigned int)smallHouse.occupiedSquares[i].x;
		int y = (unsigned int)smallHouse.occupiedSquares[i].y;
		if ((unsigned int)(x + (int)terrPos.x) >= terrainWidth - 1 || (unsigned int)(y + (int)terrPos.z) >= terrainHeight - 1 || (y + (int)terrPos.z) < 0 || (x + (int)terrPos.x) < 0) return false;
		if (gridCost[y + (int)terrPos.z][x + (int)terrPos.x] != 1) return false;
	}

	for (unsigned int i = 0; i < smallHouse.occupiedSquares.size(); i++)
	{
		unsigned int x = (unsigned int)smallHouse.occupiedSquares[i].x;
		unsigned int y = (unsigned int)smallHouse.occupiedSquares[i].y;
		XMFLOAT3 squarePos(x + (int)terrPos.x, terrPos.y, y + (int)terrPos.z);
		buildingPredictor.GetComponent<BuildingPredictor>()->AddGreen(squarePos);
	}
	return true;
}

void GameController::FindJob(JOB_ENUM _job)
{
}

vector<XMFLOAT3> GameController::AStar(XMFLOAT3 _start, XMFLOAT3 _goal)
{
	PathSearch pathSearch;
	return pathSearch.AStar(_start, _goal);
}