#pragma once
#include "GameObject.h"

class GameSaver : public Component
{
	const unsigned int id = 28;

public:
	GameSaver();
	~GameSaver();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	void Save();
	void Load();
};
