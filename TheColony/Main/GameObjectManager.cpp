#include "GameObjectManager.h"
#include "Transform.h"
#include "MeshRenderer.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Start()
{
	go.Start();
	go.AddComponent<Transform>();
}

void GameObjectManager::Update()
{
	go.Update();
}

void GameObjectManager::OnDelete()
{
	go.OnDelete();
}

void GameObjectManager::LoadFromString(string _str)
{
}