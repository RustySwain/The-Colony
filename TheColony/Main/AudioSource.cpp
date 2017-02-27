#include "AudioSource.h"
#include "Transform.h"
#include "Application.h"
#include "AudioListen.h"

using namespace DirectX;

void AudioSource::Start()
{
	emitter.SetPosition(gameObject->GetComponent<Transform>()->GetWorldPosition());
}

void AudioSource::Update()
{
	//float ratio = 0;
	//XMFLOAT3 currPos = gameObject->GetComponent<Transform>()->GetWorldPosition();
	//XMFLOAT3 camPos = Application::GetInstance()->GetGameObjectManager()->GetCamera().GetComponent<Transform>()->GetWorldPosition();
	//float dist = sqrt(pow(currPos.x - camPos.x, 2) + pow(currPos.y - camPos.y, 2) + pow(currPos.z - camPos.z, 2));
	//if(dist < radius)
	//{
	//	ratio = abs(dist / radius - 1);
	//	if (ratio < 0 || ratio > 1)
	//		ratio = 0;
	//}
	//
	//SetVolume(ratio);

	emitter.SetPosition(gameObject->GetComponent<Transform>()->GetWorldPosition());
	AudioListener listener = Camera::mainCam->gameObject->GetComponent<AudioListen>()->GetListener();
	clips[currClip]->soundEffectInstance->Apply3D(listener, emitter);
}

void AudioSource::OnDelete()
{
	for(int i = 0; i < (int)clips.size(); ++i)
	{
		SoundEffect* sfx = clips[i]->soundEffect.release();
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

	clips[currClip]->soundEffectInstance->Play(_loop);
	AudioListener listener = Camera::mainCam->gameObject->GetComponent<AudioListen>()->GetListener();
	clips[currClip]->soundEffectInstance->Apply3D(listener, emitter);
}

void AudioSource::Pause() const
{
	clips[currClip]->soundEffectInstance->Pause();
}

void AudioSource::Resume() const
{
	clips[currClip]->soundEffectInstance->Resume();
}

void AudioSource::Stop() const
{
	clips[currClip]->soundEffectInstance->Stop();
}

bool AudioSource::IsPlaying() const
{
	return clips[currClip]->soundEffect->IsInUse();
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

void AudioSource::SetVolume(float _volume)
{
	clips[currClip]->soundEffectInstance->SetVolume(_volume);
}

void AudioSource::AddAudioClip(const char * _path)
{
	AudioClip * clip = new AudioClip();
	string path = _path;
	wstring filePathW(path.size(), L'#');
	size_t outSize;
	mbstowcs_s(&outSize, &filePathW[0], path.size() + 1, path.c_str(), path.size());
	clip->soundEffect = make_unique<SoundEffect>(Application::GetInstance()->GetGameObjectManager()->GetAudioEngine().get(), filePathW.c_str());
	clip->soundEffectInstance = clip->soundEffect->CreateInstance(SoundEffectInstance_Use3D | SoundEffectInstance_ReverbUseFilters);
	clip->SetName(GetFileName(path));
	clips.push_back(clip);
}

void AudioSource::SetSoundRadius(const float _radius)
{
	radius = _radius;
}
