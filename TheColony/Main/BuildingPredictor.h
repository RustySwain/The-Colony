#pragma once
#include "GameObject.h"
#include "DirectXMath.h"

// Dependencies
// MeshRenderer
class BuildingPredictor : public Component
{
	const unsigned int id = 25;
	unsigned int vertsTaken = 0;

	static DirectX::XMFLOAT3 Project(DirectX::XMFLOAT3 _worldSpace);

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
	void AddBlue(DirectX::XMFLOAT3 _terrainPos);
	void Clear();
};
