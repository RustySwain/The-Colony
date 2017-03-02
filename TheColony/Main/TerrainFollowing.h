#pragma once
#include "GameObject.h"

class TerrainFollowing : public Component
{
	const unsigned int id = 26;

public:
	TerrainFollowing();
	~TerrainFollowing();

	// Component
	const unsigned int GetId() const override { return id; };
	void Start() override;
	void Update() override;
	void OnDelete() override;
};

