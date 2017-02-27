#pragma once
#include "Audio.h"
#include <memory>

class AudioClip
{
	std::string name;

public:
	std::unique_ptr<DirectX::SoundEffectInstance> soundEffectInstance;
	std::unique_ptr<DirectX::SoundEffect> soundEffect;

	AudioClip();
	~AudioClip();

	void SetName(std::string _name) { name = _name; }
	std::string GetName() const { return name; }
};
