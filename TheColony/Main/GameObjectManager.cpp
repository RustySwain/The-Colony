#include "GameObjectManager.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "CameraController.h"
#include "Camera.h"
#include "Time.h"
#include "TextRenderer.h"
#include "PrefabLoader.h"
#include "UIRenderer.h"
#include "Button.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Start()
{
	cube.Start();
	cube.AddComponent<Transform>();
	cube.AddComponent<MeshRenderer>()->LoadFromObj("../Assets/cube.obj");
	cube.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/crate.dds");

	text.Start();
	text.AddComponent <Transform>();
	text.AddComponent<MeshRenderer>();
	text.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Font.fontsheet", L"../Assets/Fonts/Font.dds");
	text.GetComponent<Transform>()->ScalePost(0.0005f);
	text.GetComponent<Transform>()->TranslatePost(XMFLOAT3(-1, 0, 0));
	text.GetComponent<TextRenderer>()->SetText("AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz");

	cam.Start();
	cam.AddComponent<Camera>();
	cam.AddComponent<Transform>();
	cam.GetComponent<Camera>()->SetFarPlane(500);
	cam.AddComponent<CameraController>();
	cam.GetComponent<Transform>()->SetLocalPosition(0, 0, 5);

	button.Start();
	button.AddComponent<Transform>()->SetLocalPosition(-0.5f, -0.3f, 0);
	button.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	button.AddComponent<UIRenderer>()->SetRect(0.1f, 0.1f, 0.3f, 0.3f);
	button.AddComponent<Button>()->Subscribe([&]() -> void { Callback(); });

	prefabTest.AddComponent<PrefabLoader>()->Load("test.prefab");
}

void GameObjectManager::Update()
{
	// Testing instancing stuff, feel free to remove, but it works
	static unsigned int instanceInd = 0;
	cube.GetComponent<Transform>()->RotateYPost(Time::Delta() * 90);
	if (GetAsyncKeyState('O') & 0x1)
	{
		XMMATRIX mat = XMMatrixIdentity();
		float y = (float)(rand() % 100) / 10.0f;
		mat *= XMMatrixTranslation(0, y, 0);
		cube.GetComponent<MeshRenderer>()->AddInstance(mat, instanceInd++);
	}
	if (GetAsyncKeyState('I'))
	{
		unsigned int id = rand() % instanceInd;
		cube.GetComponent<MeshRenderer>()->RemoveInstance(id);
	}
	cube.Update();
	text.Update();
	cam.Update();
	prefabTest.Update();
	button.Update();
}

void GameObjectManager::OnDelete()
{
	cube.OnDelete();
	text.OnDelete();
	cam.OnDelete();
	prefabTest.OnDelete();
	button.OnDelete();
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

void GameObjectManager::Callback()
{
	text.GetComponent<MeshRenderer>()->SetMeshColor(XMFLOAT4(1, 0, 0, 1));
}