#pragma once
#include "GameObject.h"
#include "DirectXMath.h"

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

	static XMFLOAT3 GridSquareFromTerrain(XMFLOAT3 _terrainLoc);
	bool PlaceBuilding(XMFLOAT3 _gridSquare);
	void AStar(XMFLOAT3);
	void FindJob(JOB_ENUM _job);
	float GetHours() const { return hours; }
};

