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
	go.Update();
	string test = go.GetComponent<MeshRenderer>()->WriteToString();
	go.GetComponent<MeshRenderer>()->LoadFromString(test);
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

string GameObjectManager::WriteToString() const
{
	return "";
}