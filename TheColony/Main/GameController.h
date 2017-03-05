#pragma once
#include "GameObject.h"
#include "DirectXMath.h"
#include "Mesh.h"
#include "PathSearch.h"
#include <queue>

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

	struct GameTime
	{
		float seconds = 0;
		int minutes = 0;
		int hours = 0;
		int days = 1;
		GameObject timeRender;
	};

	const unsigned int id = 23;
	GameTime gameTime;
	vector<Building> buildings;
	float** gridCost = nullptr;
	unsigned int terrainWidth, terrainHeight;
	GameObject buildingPredictor;
	static bool LoadOccupiedSquares(const char* _path, vector<XMFLOAT3>& _vec);
	PathSearch pathSearch;
	TileMap *tileMap;
	queue<GameObject*> homeless;

public:
	GameController();
	~GameController();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	// Accessors
	GameTime GetGameTime() const { return gameTime; }
	unsigned int TotalHomeless() const { return (unsigned int)homeless.size(); }

	static XMFLOAT3 GridSquareFromTerrain(XMFLOAT3 _terrainLoc);
	bool PlaceBuilding(XMFLOAT3 _gridSquare, unsigned int _rotation, unsigned int _buildingIndex);
	bool Predict(XMFLOAT3 _gridSquare, unsigned int _rotation, unsigned int _buildingIndex);
	void ClearPrediction();
	static GameObject * FindJob(GameObject * _villager);
	vector<XMFLOAT3> AStar(XMFLOAT3 _start, XMFLOAT3 _goal);
	void AddHomeless(GameObject * _object);
	void ManageGameTime();
};
