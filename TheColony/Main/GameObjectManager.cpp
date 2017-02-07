#include "GameObjectManager.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "CameraController.h"
#include "Camera.h"
#include "Time.h"
#include "Debug.h"
#include "PrefabLoader.h"
#include "Light.h"

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

	//Lighting
	lights.Start();
	lights.AddComponent<Light>()->SetColor(XMFLOAT4(1, 1, 1, 1));
	lights.AddComponent<Transform>();
	lights.GetComponent<Transform>()->RotateYPre(180);
	lights.GetComponent<Transform>()->RotateXPre(-50);
	lights.GetComponent<Transform>()->RotateZPre(-15);
	lights.GetComponent<Transform>()->SetLocalPosition(0, 3, -2);
	lights.GetComponent<Light>()->type = Light::SPOT;
	lights.GetComponent<Light>()->SetExtra(XMFLOAT4(100, 0.97, 0, 1));

	prefabTest.AddComponent<PrefabLoader>()->Load("test.prefab");
}

void GameObjectManager::Update()
{
	//Rotate light
	lights.GetComponent<Transform>()->RotateYPost(Time::Delta() * 100);

	// Testing instancing stuff, feel free to remove, but it works
	static unsigned int instanceInd = 0;
	//go.GetComponent<Transform>()->RotateYPost(Time::Delta() * 90);
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
	lights.Update();
}

void GameObjectManager::OnDelete()
{
	go.OnDelete();
	cam.OnDelete();
	prefabTest.OnDelete();
	lights.OnDelete();
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