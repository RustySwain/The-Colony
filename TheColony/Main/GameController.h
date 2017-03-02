#pragma once
#include "GameObject.h"
#include "DirectXMath.h"
#include "Mesh.h"
#include "PathSearch.h"

using namespace DirectX;

enum JOB_ENUM { No_Job = 0, Farmer, Builder, Forester, Miner, Metalworker, Teacher, Physician };
enum ITEM_ENUM { Wood = 0, Stone, Iron, Coal, Cabbage, Corn, Potato, Berries };

class GameController : public Component
{
	struct Building
	{
		GameObject* instances = nullptr;
		vector<GameObject*> colliders;
		Mesh* collisionMesh = nullptr;
		vector<XMFLOAT3> occupiedSquares;
	};

	const unsigned int id = 23;
	float gameTime = 0;
	float hours = 0;
	vector<Building> buildings;
	float** gridCost = nullptr;
	unsigned int terrainWidth, terrainHeight;
	GameObject buildingPredictor;
	static bool LoadOccupiedSquares(const char* _path, vector<XMFLOAT3>& _vec);
	PathSearch pathSearch;
	TileMap *tileMap;

public:
	GameController();
	~GameController();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	// Accessors
	float GetHours() const { return hours / 3600; }

	static XMFLOAT3 GridSquareFromTerrain(XMFLOAT3 _terrainLoc);
	bool PlaceBuilding(XMFLOAT3 _gridSquare, unsigned int _rotation, unsigned int _buildingIndex);
	bool Predict(XMFLOAT3 _gridSquare, unsigned int _rotation, unsigned int _buildingIndex);
	void ClearPrediction();
	static void FindJob(JOB_ENUM _job);
	vector<XMFLOAT3> AStar(XMFLOAT3 _start, XMFLOAT3 _goal);
};
