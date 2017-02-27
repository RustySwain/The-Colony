#include "GameObjectManager.h"
#include "Transform.h"
#include "CameraController.h"
#include "Camera.h"
#include "Time.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "AudioListen.h"
#include "GameScene.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Start()
{
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_EnvironmentalReverb | AudioEngine_ReverbUseFilters;
#ifdef _DEBUG
	eflags = eflags | AudioEngine_Debug;
#endif
	audioEngine.reset(new AudioEngine(eflags));
	audioEngine->SetReverb(Reverb_Default);

	scene.Start();
	scene.AddComponent<SceneManager>();
	scene.AddComponent<GameScene>();

	cam.SetId(2);
	cam.SetTag("Untagged");
	cam.Start();
	cam.AddComponent<Camera>();
	cam.AddComponent<Transform>();
	cam.GetComponent<Camera>()->SetFarPlane(5000);
	cam.AddComponent<CameraController>();
	cam.GetComponent<Transform>()->SetLocalPosition(0, 10, 5);
	cam.GetComponent<Transform>()->RotateXPre(-40);
	cam.AddComponent<AudioListen>();
}

void GameObjectManager::Update()
{
	totalTime += Time::Delta();

	// Uncomment the next line for a sweet progress  bar
	//button.GetComponent<ProgressBar>()->SetRatio(totalTime * 0.1f);

	cam.Update();
	scene.Update();
}

void GameObjectManager::OnDelete()
{
	AudioEngine* sfx = audioEngine.release();
	delete sfx;

	cam.OnDelete();
	scene.OnDelete();
}

void GameObjectManager::LoadFromFile(fstream & _file)
{
}