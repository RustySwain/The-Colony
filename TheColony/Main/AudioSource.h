#pragma once
#include "GameObject.h"
#include "AudioClip.h"
#include <Audio.h>

/* Dependencies:
	- Transform
*/
namespace DirectX
{
	class AudioSource : public Component
	{
		const unsigned int id = 11;
		AudioEmitter emitter;
		vector<AudioClip*> clips;
		int currClip;
		float radius;

	public:
		AudioSource() {}
		~AudioSource() override {}

		// Component
		const unsigned int GetId() const override { return id; };
		void Start() override;
		void Update() override;
		void OnDelete() override;

		/*bool _loop: loop sound or play one-shot*/
		void Play(const char * _clip, bool _loop);
		void Pause() const;
		void Resume() const;
		void Stop() const;
		bool IsPlaying() const;

		string GetFileName(const string & _file);
		string RemoveSufix(const string & _input);

		// Mutators
		/*float _volume: 0.0f (silence) to 1.0f (full volume)*/
		void SetVolume(float _volume);
		void AddAudioClip(const char * _path);
		void SetSoundRadius(const float _radius);
	};
}
