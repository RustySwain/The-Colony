#include "GameObjectManager.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "CameraController.h"
#include "Camera.h"

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
<<<<<<< HEAD

	cam.Start();
	cam.AddComponent<Camera>();
	cam.AddComponent<Transform>();
	cam.GetComponent<Camera>()->SetFarPlane(500);
	cam.AddComponent<CameraController>();
	//cam.GetComponent<Transform>()->SetLocalPosition(4, 4, 20);
=======
	go.Update();
	string test = go.GetComponent<MeshRenderer>()->WriteToString();
	go.GetComponent<MeshRenderer>()->LoadFromString(test);
>>>>>>> origin/master
}

void GameObjectManager::Update()
{
	go.Update();
	cam.Update();
}

void GameObjectManager::OnDelete()
{
	go.OnDelete();
	cam.OnDelete();
}

void GameObjectManager::LoadFromString(string _str)
{
}

string GameObjectManager::WriteToString() const
{
	return "";
}