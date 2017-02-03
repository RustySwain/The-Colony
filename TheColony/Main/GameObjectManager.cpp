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
	go.AddComponent<MeshRenderer>()->LoadFromObj("../Assets/cube.obj");
	go.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/crate.dds");
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