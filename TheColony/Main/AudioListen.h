#pragma once
#include "GameObject.h"
#include <Audio.h>

class AudioListen : public Component
{
	const unsigned int id = 1;
	DirectX::AudioListener listener;

public:
	AudioListen() {}
	~AudioListen() {}

	// Component
	const unsigned int GetId() const override { return id; };
	void Start() override;
	void Update() override;
	void OnDelete() override;

	DirectX::AudioListener &GetListener() { return listener; }
};