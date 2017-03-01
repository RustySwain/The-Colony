#pragma once
#include "GameObject.h"
#include "DirectXMath.h"

// Dependencies
// MeshRenderer
class BuildingPredictor : public Component
{
	const unsigned int id = 25;
	unsigned int vertsTaken = 0;

public:
	BuildingPredictor();
	~BuildingPredictor();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	void AddGreen(DirectX::XMFLOAT3 _terrainPos);
	void AddRed(DirectX::XMFLOAT3 _terrainPos);
	void Clear();
};
