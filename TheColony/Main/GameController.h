#pragma once
#include "GameObject.h"
#include "DirectXMath.h"

enum JOB_ENUM { No_Job = 0, Farmer, Builder, Forester, Miner, Metalworker, Teacher, Physician };
enum ITEM_ENUM { Wood = 0, Stone, Iron, Coal, Cabbage, Corn, Potato, Berries };


class GameController : public Component
{
	const unsigned int id = 23;
	float gameTime = 0;
	float hours = 0;

public:
	static GameController* gameController;

	GameController();
	~GameController();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	// Accessors
	float GetGameTime() const { return gameTime; }
	float GetHours() const { return hours; }

	static DirectX::XMFLOAT3 GridSquareFromTerrain(DirectX::XMFLOAT3 _terrainLoc);
	void AStar(DirectX::XMFLOAT3);
	void FindJob(JOB_ENUM _job);
};
