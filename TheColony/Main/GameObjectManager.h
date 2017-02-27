#pragma once
#include "GameObject.h"
#include <Audio.h>

// Dependencies: None
class GameObjectManager : public Component
{
	const unsigned int id = 5;

	GameObject scene;
	GameObject cam;
	unique_ptr<DirectX::AudioEngine> audioEngine;

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

	GameObject& GetScene() { return scene; }
	unique_ptr<DirectX::AudioEngine>& GetAudioEngine() { return audioEngine; }
};
