#include "SceneManager.h"
#include "MainMenu.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Start()
{
}

void SceneManager::Update()
{
	if (flag)
	{
		gameObject->RemoveComponent<MainMenu>();
		flag = false;
	}
}

void SceneManager::OnDelete()
{
}