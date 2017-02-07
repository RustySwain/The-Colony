#pragma once
#include "GameObject.h"

// Dependencies: None
class GameObjectManager : public Component
{
	const unsigned int id = 5;
	GameObject cube;
	GameObject cam;
	GameObject spotLight;
	GameObject dirLight;
	GameObject pointLight;
	GameObject prefabTest;
	GameObject text;

public:
	GameObjectManager();
	~GameObjectManager();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromFile(fstream &_file) override;
	virtual void LoadFromString(string _str) override;
	virtual string WriteToString() const override;
};
