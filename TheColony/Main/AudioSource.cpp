#include "AudioSource.h"

using namespace DirectX;

void AudioSource::Start()
{
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
	//AUDIO_ENGINE_FLAGS eflags = AudioEngine_EnvironmentalReverb | AudioEngine_ReverbUseFilters;
#ifdef _DEBUG
	eflags = eflags | AudioEngine_Debug;
#endif
	audioEngine.reset(new AudioEngine(eflags));
	audioEngine->SetReverb(Reverb_ConcertHall);
	currClip = 0;
}

void AudioSource::Update()
{
}

void AudioSource::OnDelete()
{
	AudioEngine* ae = audioEngine.release();
	delete ae;

	for(int i = 0; i < (int)clips.size(); ++i)
	{
		SoundEffect* sfx = clips[i]->soundFX.release();
		delete sfx;
		delete clips[i];
	}
}

void AudioSource::Play(const char * _clip, bool _loop)
{
	for(int i = 0; i < (int)clips.size(); ++i)
	{
		if (clips[i]->GetName() == _clip)
			currClip = i;
	}

	clips[currClip]->soundFXInstance->Play(_loop);
}

void AudioSource::Pause() const
{
	clips[currClip]->soundFXInstance->Pause();
}

void AudioSource::Resume() const
{
	clips[currClip]->soundFXInstance->Resume();
}

void AudioSource::Stop() const
{
	clips[currClip]->soundFXInstance->Stop();
}

bool AudioSource::IsPlaying() const
{
	return clips[currClip]->soundFX->IsInUse();
}

string AudioSource::GetFileName(const string & _file)
{
	string seperator("/");
	unsigned int pos = (unsigned int)_file.find_last_of(seperator);
	if (pos != string::npos)
		return RemoveSufix(_file.substr(pos + 1));

	return _file;
}

string AudioSource::RemoveSufix(const string & _input)
{
	string seperator(".");
	unsigned int pos = (unsigned int)_input.find_last_of(seperator);
	if (pos != string::npos)
		return _input.substr(0, pos);

	return _input;
}

void AudioSource::SetAudioEngineFlags(AUDIO_ENGINE_FLAGS _eflags)
{
	audioEngine.reset(new AudioEngine(_eflags));
}

void AudioSource::SetVolume(float _volume) const
{
	clips[currClip]->soundFXInstance->SetVolume(_volume);
}

void AudioSource::AddAudioClip(const char * _path)
{
	AudioClip * clip = new AudioClip();
	string path = _path;
	wstring filePathW(path.size(), L'#');
	size_t outSize;
	mbstowcs_s(&outSize, &filePathW[0], path.size() + 1, path.c_str(), path.size());
	clip->soundFX.reset(new SoundEffect(audioEngine.get(), filePathW.c_str()));
	clip->soundFXInstance = clip->soundFX->CreateInstance(SoundEffectInstance_Use3D | SoundEffectInstance_ReverbUseFilters);
	clip->SetName(GetFileName(path));
	clips.push_back(clip);
}
