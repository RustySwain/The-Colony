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
#include "Defines.h"
#include "VillagerController.h"

bool GameController::LoadOccupiedSquares(const char* _path, vector<XMFLOAT3>& _vec)
{
	ifstream reader(_path, ios_base::in);
	if (reader.is_open())
	{
		while (!reader.eof())
		{
			char buffer[256];
			reader.getline(buffer, 256);
			stringstream sstream(buffer);
			XMFLOAT3 fl2;
			sstream >> fl2.x >> fl2.y >> fl2.z;
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
	buildings.push_back(Building());
	buildings[0].instances = new GameObject();
	buildings[0].instances->Start();
	buildings[0].instances->AddComponent<Transform>();
	buildings[0].instances->AddComponent<MeshRenderer>()->LoadFromObj("../Assets/Buildings/SmallHousePlaceHolder.obj");
	buildings[0].instances->GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/bark.dds");
	buildings[0].collisionMesh = new Mesh();
	buildings[0].collisionMesh->LoadFromObj("../Assets/Buildings/SmallHouseCollision.obj");
	LoadOccupiedSquares("../Assets/Buildings/SmallHouse.building", buildings[0].occupiedSquares);
	buildings.push_back(Building());
	buildings[1].instances = new GameObject();
	buildings[1].instances->Start();
	buildings[1].instances->AddComponent<Transform>();
	buildings[1].instances->AddComponent<MeshRenderer>()->LoadFromObj("../Assets/Buildings/MedHousePlaceHolder.obj");
	buildings[1].instances->GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/bark.dds");
	buildings[1].collisionMesh = new Mesh();
	buildings[1].collisionMesh->LoadFromObj("../Assets/Buildings/MedHouseCollision.obj");
	LoadOccupiedSquares("../Assets/Buildings/MedHouse.building", buildings[1].occupiedSquares);

	buildingPredictor.Start();
	buildingPredictor.AddComponent<Transform>();
	buildingPredictor.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/White.dds");
	buildingPredictor.AddComponent<BuildingPredictor>();

	// Create TileMap
	GameObject* terrain = GameObject::FindFromTag("Terrain")[0];
	unsigned int width = terrain->GetComponent<Terrain>()->GetWidth();
	unsigned int height = terrain->GetComponent<Terrain>()->GetHeight();

	tileMap = new TileMap();
	tileMap->createTileArray(width, height);

	for (unsigned int x = 0; x < width; ++x)
	{
		for (unsigned int z = 0; z < height; ++z)
		{
			tileMap->addTile(x, z, 1);
		}
	}
	pathSearch.initialize(tileMap);
}

void GameController::Update()
{
	gameTime += Time::Delta();
	hours += gameTime;
	if (hours >= 86400)
		hours = 0;

	for (unsigned int i = 0; i < buildings.size(); i++)
	{
		buildings[i].instances->Update();
		for (unsigned int j = 0; j < buildings[i].colliders.size(); j++)
		{
			buildings[i].colliders[j]->Update();
		}
	}
	static bool updated = false;
	if (!updated)
	{
		updated = true;
		for (unsigned int i = 0; i < buildings.size(); i++)
			buildings[i].instances->GetComponent<MeshRenderer>()->RemoveInstance(-1);
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
	for (unsigned int i = 0; i < buildings.size(); i++)
	{
		buildings[i].instances->OnDelete();
		delete buildings[i].instances;
		for (unsigned int j = 0; j < buildings[i].colliders.size(); j++)
		{
			buildings[i].colliders[j]->OnDelete();
			delete buildings[i].colliders[j];
		}
		delete buildings[i].collisionMesh;
	}

	for (unsigned int i = 0; i < terrainHeight; i++)
		delete[] gridCost[i];
	delete[] gridCost;
	buildingPredictor.OnDelete();

	delete tileMap;
}

XMFLOAT3 GameController::GridSquareFromTerrain(XMFLOAT3 _terrainLoc)
{
	GameObject* terrain = GameObject::FindFromTag("Terrain")[0];
	XMFLOAT4 pos = terrain->GetComponent<MeshRenderer>()->GetMesh()->GetVertexData()[(int)_terrainLoc.x * terrain->GetComponent<Terrain>()->GetHeight() + (int)_terrainLoc.z].position;
	return XMFLOAT3(pos.x, pos.y, pos.z);
}

bool GameController::PlaceBuilding(XMFLOAT3 _gridSquare, unsigned int _rotation, unsigned int _buildingIndex)
{
	XMFLOAT3 terrPos = GridSquareFromTerrain(_gridSquare);

	for (unsigned int i = 0; i < buildings[_buildingIndex].occupiedSquares.size(); i++)
	{
		XMMATRIX tmp = XMMatrixTranslation(buildings[_buildingIndex].occupiedSquares[i].x, buildings[_buildingIndex].occupiedSquares[i].y, 0) * XMMatrixRotationZ(_rotation * 90.0f * DEG2RAD);
		int x = (int)round(tmp.r[3].m128_f32[0]);
		int y = (int)round(tmp.r[3].m128_f32[1]);
		if ((unsigned int)(x + (int)terrPos.x) >= terrainWidth - 1 || (unsigned int)(y + (int)terrPos.z) >= terrainHeight - 1 || (y + (int)terrPos.z) < 0 || (x + (int)terrPos.x) < 0) return false;
		if (gridCost[y + (int)terrPos.z][x + (int)terrPos.x] != 1) return false;
	}

	for (unsigned int i = 0; i < buildings[_buildingIndex].occupiedSquares.size(); i++)
	{
		XMMATRIX tmp = XMMatrixTranslation(buildings[_buildingIndex].occupiedSquares[i].x, buildings[_buildingIndex].occupiedSquares[i].y, 0) * XMMatrixRotationZ(_rotation * 90.0f * DEG2RAD);
		int x = (int)round(tmp.r[3].m128_f32[0]);
		int y = (int)round(tmp.r[3].m128_f32[1]);
		if ((unsigned int)(x + (int)terrPos.x) >= terrainWidth - 1 || (unsigned int)(y + (int)terrPos.z) >= terrainHeight - 1 || (y + (int)terrPos.z) < 0 || (x + (int)terrPos.x) < 0) return false;
		gridCost[y + (int)terrPos.z][x + (int)terrPos.x] = 0;

		// Set front door
		if (buildings[_buildingIndex].occupiedSquares[i].z == 2)
		{
		}

		// Update tile map
		if (buildings[_buildingIndex].occupiedSquares[i].z == 0)
		{
			Tile * tile = tileMap->getTile(x + (int)terrPos.x, y + (int)terrPos.z);
			pathSearch.ChangeTileCost(tile, 0);
		}

		// Notifiy all villagers that a new building was placed
		vector<GameObject*> villagers = GameObject::FindFromTag("Villager");
		for (int v = 0; v < (int)villagers.size(); ++v)
			villagers[v]->GetComponent<VillagerController>()->Notify();
	}

	XMMATRIX translation = XMMatrixRotationY(_rotation * 90.0f * -DEG2RAD) * XMMatrixTranslation(0.5f, 0, 0.5f) * XMMatrixTranslation(terrPos.x, terrPos.y, terrPos.z);
	buildings[_buildingIndex].instances->GetComponent<MeshRenderer>()->AddInstance(translation, (int)_gridSquare.x * GameObject::FindFromTag("Terrain")[0]->GetComponent<Terrain>()->GetHeight() + (int)_gridSquare.z);

	GameObject* nuCollider = new GameObject();
	nuCollider->SetTag("House");
	nuCollider->Start();
	nuCollider->AddComponent<Transform>()->RotateYPre(_rotation * -90.0f);
	nuCollider->GetComponent<Transform>()->TranslatePost(XMFLOAT3(0.5f, 0, 0.5f));
	nuCollider->GetComponent<Transform>()->TranslatePost(XMFLOAT3(terrPos.x, terrPos.y, terrPos.z));
	nuCollider->AddComponent<Collider>()->SetMesh(buildings[_buildingIndex].collisionMesh);
	buildings[_buildingIndex].colliders.push_back(nuCollider);
	if (0 == _buildingIndex)
	{
	}

	return true;
}

bool GameController::Predict(XMFLOAT3 _gridSquare, unsigned int _rotation, unsigned int _buildingIndex)
{
	XMFLOAT3 terrPos = GridSquareFromTerrain(_gridSquare);

	for (unsigned int i = 0; i < buildings[_buildingIndex].occupiedSquares.size(); i++)
	{
		XMMATRIX tmp = XMMatrixTranslation(buildings[_buildingIndex].occupiedSquares[i].x, buildings[_buildingIndex].occupiedSquares[i].y, 0) * XMMatrixRotationZ(_rotation * 90.0f * DEG2RAD);
		int x = (int)round(tmp.r[3].m128_f32[0]);
		int y = (int)round(tmp.r[3].m128_f32[1]);
		if ((unsigned int)(x + (int)terrPos.x) >= terrainWidth - 1 || (unsigned int)(y + (int)terrPos.z) >= terrainHeight - 1 || (y + (int)terrPos.z) < 0 || (x + (int)terrPos.x) < 0) return false;
		XMFLOAT3 squarePos((float)x + terrPos.x, terrPos.y, (float)y + terrPos.z);
		if (gridCost[y + (int)terrPos.z][x + (int)terrPos.x] != 1)
			buildingPredictor.GetComponent<BuildingPredictor>()->AddColor(squarePos, XMFLOAT4(1, 0, 0, 0.5f));
	}

	for (unsigned int i = 0; i < buildings[_buildingIndex].occupiedSquares.size(); i++)
	{
		XMMATRIX tmp = XMMatrixTranslation(buildings[_buildingIndex].occupiedSquares[i].x, buildings[_buildingIndex].occupiedSquares[i].y, 0) * XMMatrixRotationZ(_rotation * 90.0f * DEG2RAD);
		int x = (int)round(tmp.r[3].m128_f32[0]);
		int y = (int)round(tmp.r[3].m128_f32[1]);
		XMFLOAT3 squarePos((float)x + terrPos.x, terrPos.y, (float)y + terrPos.z);
		if (buildings[_buildingIndex].occupiedSquares[i].z == 0)
			buildingPredictor.GetComponent<BuildingPredictor>()->AddColor(squarePos, XMFLOAT4(0, 1, 0, 0.5f));
		else if (buildings[_buildingIndex].occupiedSquares[i].z == 1)
			buildingPredictor.GetComponent<BuildingPredictor>()->AddColor(squarePos, XMFLOAT4(0, 0.807f, 0.819f, 0.5f));
		else if (buildings[_buildingIndex].occupiedSquares[i].z == 2)
			buildingPredictor.GetComponent<BuildingPredictor>()->AddColor(squarePos, XMFLOAT4(1, 1, 0, 0.5f));
	}
	return true;
}

void GameController::ClearPrediction()
{
	buildingPredictor.GetComponent<BuildingPredictor>()->Clear();
}

void GameController::FindJob(JOB_ENUM _job)
{
}

vector<XMFLOAT3> GameController::AStar(XMFLOAT3 _start, XMFLOAT3 _goal)
{
	XMFLOAT3 start = GridSquareFromTerrain(_start);
	XMFLOAT3 goal = GridSquareFromTerrain(_goal);
	return pathSearch.AStar(start, goal);
}