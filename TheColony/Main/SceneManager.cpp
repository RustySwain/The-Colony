#include "SceneManager.h"
#include "LoadingScreen.h"
#include "UIRenderer.h"

void SceneManager::InitScene()
{
	gameObject->GetComponent<MainMenu>()->Init();
	mtex.lock();
	doneLoading = true;
	mtex.unlock();
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Start()
{
	loadingScreen.SetTag("LoadingScreen");
	loadingScreen.Start();
	loadingScreen.AddComponent<Transform>();
	loadingScreen.AddComponent<MeshRenderer>();
	loadingScreen.AddComponent<UIRenderer>();
	loadingScreen.AddComponent<LoadingScreen>();
	loadingScreen.SetEnabled(false);
}

void SceneManager::Update()
{
	if (shouldLoad)
	{
		shouldLoad = false;
		gameObject->RemoveComponent<MainMenu>();
		//loadingThread = thread(&SceneManager::InitScene, this);
		InitScene();
	}
	mtex.lock();
	if (doneLoading)
	{
		//loadingThread.join();
		doneLoading = false;
		gameObject->GetComponent<MainMenu>()->SetEnabled(true);
	}
	mtex.unlock();
	loadingScreen.Update();
}

void SceneManager::OnDelete()
{
	loadingScreen.OnDelete();
}