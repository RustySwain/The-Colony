#pragma once
#include "GameObject.h"
#include "Button.h"

// Dependencies: None
class GameObjectManager : public Component
{
	const unsigned int id = 5;
	GameObject cube;
	GameObject cam;
	GameObject spotLight;
	GameObject dirLight;
	GameObject pointLight;
	GameObject text;
	GameObject button;
	GameObject skybox;

	// Test objects
	GameObject teddy, box;

	CallbackFunc func;

	float color = 0;

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

	void Callback();
};
