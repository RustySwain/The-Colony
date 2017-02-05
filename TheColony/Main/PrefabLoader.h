#pragma once
#include "GameObject.h"

// Dependencies: None
class PrefabLoader : public Component
{
	const unsigned int id = 12;

public:
	PrefabLoader();
	~PrefabLoader();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromString(string _str) override;

	void Load(string _path);
};
