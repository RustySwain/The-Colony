#pragma once
#include "GameObject.h"
class GameObjectManager : public Component
{
	const unsigned int id = 5;
	GameObject go;
	GameObject cam;

public:
	GameObjectManager();
	~GameObjectManager();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromString(string _str) override;
};
