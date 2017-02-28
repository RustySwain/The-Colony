#pragma once
#include "GameObject.h"

// Dependencies
// MeshRenderer
class BuildingPredictor : public Component
{
	const unsigned int id = 25;

public:
	BuildingPredictor();
	~BuildingPredictor();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
};
