#pragma once
#include "GameObject.h"

// Dependencies
// MeshRenderer
class UIRenderer : public Component
{
	const unsigned int id = 14;

public:
	UIRenderer();
	~UIRenderer();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromFile(fstream &_file) override;
	virtual void LoadFromString(string _str) override;
	virtual string WriteToString() const override;
};
