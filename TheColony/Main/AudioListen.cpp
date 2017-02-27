#include "AudioListen.h"
#include "Transform.h"

void AudioListen::Start()
{
	listener.SetPosition(gameObject->GetComponent<Transform>()->GetWorldPosition());
}

void AudioListen::Update()
{
	listener.SetPosition(gameObject->GetComponent<Transform>()->GetWorldPosition());
}

void AudioListen::OnDelete()
{
}
