#pragma once
#include "GameObject.h"
#include "Button.h"

// Dependencies: None
class GameObjectManager : public Component
{
	const unsigned int id = 5;
	vector<GameObject*> gameObjects;

	GameObject cube;
	GameObject cam;
	GameObject spotLight;
	GameObject dirLight;
	GameObject pointLight;
	GameObject text;
	GameObject button;
	GameObject skybox;
	GameObject terrain;
	//GameObject scene;
	GameObject box;

	CallbackFunc func;

	float color = 0;
	float totalTime = 0;

public:
	GameObjectManager();
	~GameObjectManager();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromFile(fstream &_file) override;

	vector<GameObject*>& GameObjects() { return gameObjects; }

	void Callback();
};
