#pragma once
#include "GameObject.h"
#include <DirectXMath.h>

class PlayerController : public Component
{
	const unsigned int id = 21;

	unsigned int rotation = 0;

public:
	PlayerController();
	~PlayerController();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
};
