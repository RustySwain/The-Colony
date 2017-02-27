#pragma once
#include "GameObject.h"
#include "DirectXMath.h"

class GameController : public Component
{
	const unsigned int id = 23;

public:
	GameController();
	~GameController();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	static DirectX::XMFLOAT3 GridSquareFromTerrain(DirectX::XMFLOAT3 _terrainLoc);
};
