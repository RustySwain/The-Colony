#include "SceneManager.h"
#include "MainMenu.h"
#include "LoadingScreen.h"
#include "UIRenderer.h"

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
	loadingScreen.AddComponent<MeshRenderer>();
	loadingScreen.AddComponent<UIRenderer>();
	loadingScreen.AddComponent<LoadingScreen>();
	loadingScreen.SetEnabled(false);
}

void SceneManager::Update()
{
	if (flag)
	{
		gameObject->RemoveComponent<MainMenu>();
		flag = false;
	}
	loadingScreen.Update();
}

void SceneManager::OnDelete()
{
	loadingScreen.OnDelete();
}