#pragma once
#include "GameObject.h"
#include "DirectXMath.h"
#include "PriorityQueue.h"
#include <unordered_map>

using namespace DirectX;

enum JOB_ENUM { No_Job = 0, Farmer, Builder, Forester, Miner, Metalworker, Teacher, Physician };
enum ITEM_ENUM { Wood = 0, Stone, Iron, Coal, Cabbage, Corn, Potato, Berries };

class GameController : public Component
{
	const unsigned int id = 23;
	float gameTime = 0;
	float hours = 0;

	struct Building
	{
		GameObject instances;
		vector<GameObject> colliders;
	};

public:
	GameController();
	~GameController();
	Building smallHouse;

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	// Accessors
	float GetHours() const { return hours / 3600; }

	static XMFLOAT3 GridSquareFromTerrain(XMFLOAT3 _terrainLoc);
	bool PlaceBuilding(XMFLOAT3 _gridSquare);
	static void FindJob(JOB_ENUM _job);
	static vector<XMFLOAT3> AStar(XMFLOAT3 _start, XMFLOAT3 _goal);
};
