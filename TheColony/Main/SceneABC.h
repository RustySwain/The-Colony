#pragma once
#include "GameObject.h"

class SceneABC : public Component
{
	const unsigned int id = 19;

public:

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void LoadFromFile(fstream& _file) override {};
};
