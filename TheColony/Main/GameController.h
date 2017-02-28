#pragma once
#include "GameObject.h"
#include "DirectXMath.h"

using namespace DirectX;

enum JOB_ENUM { No_Job = 0, Farmer, Builder, Forester, Miner, Metalworker, Teacher, Physician };
enum ITEM_ENUM { Wood, };

class GameController : public Component
{
	struct Building
	{
		GameObject instances;
		vector<GameObject> colliders;
	};

	const unsigned int id = 23;
	Building smallHouse;

public:
	GameController();
	~GameController();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	static XMFLOAT3 GridSquareFromTerrain(XMFLOAT3 _terrainLoc);
	bool PlaceBuilding(XMFLOAT3 _gridSquare);
	void AStar(XMFLOAT3);
	void FindJob(JOB_ENUM _job);
};
