#pragma once
#include "GameObject.h"

// Dependencies
// MeshRenderer
class Skybox : public Component
{
	const unsigned int id = 9;

public:
	Skybox();
	~Skybox();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
};
