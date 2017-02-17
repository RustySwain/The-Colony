#include "SceneManager.h"
#include "SceneABC.h"

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
	if(flag)
	{
		gameObject->RemoveComponent<SceneABC>();
		flag = false;
	}
}

void SceneManager::OnDelete()
{
}
