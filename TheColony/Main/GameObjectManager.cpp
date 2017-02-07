#include "GameObjectManager.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "CameraController.h"
#include "Camera.h"
#include "Time.h"
#include "Debug.h"
#include "PrefabLoader.h"

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

	prefabTest.AddComponent<PrefabLoader>()->Load("../Assets/Box.prefab");
	prefabTest.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/Box.dds");
}

void GameObjectManager::Update()
{
	// Testing instancing stuff, feel free to remove, but it works
	static unsigned int instanceInd = 0;
	go.GetComponent<Transform>()->RotateYPost(Time::Delta() * 90);
	if (GetAsyncKeyState('O') & 0x1)
	{
		XMMATRIX mat = XMMatrixIdentity();
		float y = (float)(rand() % 100) / 10.0f;
		mat *= XMMatrixTranslation(0, y, 0);
		go.GetComponent<MeshRenderer>()->AddInstance(mat, instanceInd++);
	}
	if (GetAsyncKeyState('I'))
	{
		unsigned int id = rand() % instanceInd;
		go.GetComponent<MeshRenderer>()->RemoveInstance(id);
	}
	go.Update();
	cam.Update();
	prefabTest.Update();
}

void GameObjectManager::OnDelete()
{
	go.OnDelete();
	cam.OnDelete();
	prefabTest.OnDelete();
}

void GameObjectManager::LoadFromFile(fstream & _file)
{
}

void GameObjectManager::LoadFromString(string _str)
{
}

string GameObjectManager::WriteToString() const
{
	return "";
}