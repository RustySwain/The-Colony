#pragma once
#include "GameObject.h"

class SceneABC : public Component
{
	const unsigned int id = 19;

public:
	SceneABC();
	~SceneABC();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromFile(fstream &_file) override {}
};
