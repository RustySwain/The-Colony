#pragma once
#include "GameObject.h"
#include <Audio.h>

namespace DirectX
{
	class AudioListen : public Component
	{
		const unsigned int id = 12;
		AudioListener listener;

	public:
		AudioListen() {}
		~AudioListen() {}

		// Component
		const unsigned int GetId() const override { return id; };
		void Start() override;
		void Update() override;
		void OnDelete() override;

		AudioListener& GetListener() { return listener; }
	};
}
