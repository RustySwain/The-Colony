#pragma once
#include "Audio.h"
#include <memory>

class AudioClip
{
	std::string name;

public:
	std::unique_ptr<DirectX::SoundEffectInstance> soundFXInstance;
	std::unique_ptr<DirectX::SoundEffect> soundFX;

	AudioClip();
	~AudioClip();

	void SetName(std::string _name) { name = _name; }
	std::string GetName() const { return name; }
};
