#pragma once
#include "GameObject.h"
#include "AudioClip.h"

class AudioSource : public Component
{
	const unsigned int id = 11;
	unique_ptr<DirectX::AudioEngine> audioEngine;
	vector<AudioClip*> clips;
	int currClip;

public:
	AudioSource() {}
	~AudioSource() override {}

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	/*bool _loop: loop sound or play one-shot*/
	void Play(const char * _clip, bool _loop);
	void Pause() const;
	void Resume() const;
	void Stop() const;
	bool IsPlaying() const;

	string GetFileName(const string & _file);
	string RemoveSufix(const string & _input);

	// Mutators
	void SetAudioEngineFlags(DirectX::AUDIO_ENGINE_FLAGS _eflags);
	/*float _volume: 0.0f (silence) to 1.0f (full volume)*/
	void SetVolume(float _volume) const;
	void AddAudioClip(const char * _path);
};
