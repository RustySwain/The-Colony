#include "GameObjectManager.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "CameraController.h"
#include "Camera.h"
#include "Time.h"

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

	cam.Start();
	cam.AddComponent<Camera>();
	cam.AddComponent<Transform>();
	cam.GetComponent<Camera>()->SetFarPlane(500);
	cam.AddComponent<CameraController>();
	cam.GetComponent<Transform>()->SetLocalPosition(0, 0, 5);
}

void GameObjectManager::Update()
{
	go.GetComponent<Transform>()->RotateYPost(Time::Delta() * 90);
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