#pragma once
#include "GameObject.h"
#include "Application.h"

class SceneManager : public Component
{
	const unsigned int id = 18;

protected:
	vector<GameObject*> gameObjects;
	CallbackFunc func;

public:
	SceneManager();
	~SceneManager();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromFile(fstream &_file) override {}

	virtual void Callback();

	// Accessors
	vector<GameObject*> GetGameObjects() const { return gameObjects; }
};
