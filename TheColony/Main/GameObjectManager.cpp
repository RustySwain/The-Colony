#include "GameObjectManager.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "CameraController.h"
#include "Camera.h"
#include "Time.h"
#include "PrefabLoader.h"
#include "UIRenderer.h"
#include "Button.h"
#include "Light.h"
#include "TextRenderer.h"
#include "Skybox.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Start()
{
	skybox.Start();
	skybox.AddComponent<Transform>()->ScalePost(100);
	skybox.AddComponent<MeshRenderer>();
	skybox.AddComponent<Skybox>();

	cube.Start();
	cube.AddComponent<Transform>();
	cube.AddComponent<MeshRenderer>()->LoadFromObj("../Assets/cube.obj");
	cube.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/crate.dds");

	cam.Start();
	cam.AddComponent<Camera>();
	cam.AddComponent<Transform>();
	cam.GetComponent<Camera>()->SetFarPlane(500);
	cam.AddComponent<CameraController>();
	cam.GetComponent<Transform>()->SetLocalPosition(0, 0, 5);

	button.Start();
	button.AddComponent<Transform>()->SetLocalPosition(-0.4f, -0.7f, 0);
	button.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	button.AddComponent<UIRenderer>()->SetRect(0.1f, 0.1f, 0.3f, 0.3f);
	button.AddComponent<Button>()->Subscribe([=]() -> void { Callback(); });

	text.Start();
	text.AddComponent <Transform>();
	text.AddComponent<MeshRenderer>();
	text.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Font.fontsheet", L"../Assets/Fonts/Font.dds");
	text.GetComponent<Transform>()->ScalePost(0.0005f);
	text.GetComponent<Transform>()->TranslatePost(XMFLOAT3(-0.3f, 0, 0));
	text.GetComponent<TextRenderer>()->SetText("Hello, World!");

	//Lighting
	spotLight.Start();
	spotLight.AddComponent<Light>()->SetColor(XMFLOAT4(1, 1, 1, 1));
	spotLight.AddComponent<Transform>();
	spotLight.GetComponent<Transform>()->RotateYPre(180);
	spotLight.GetComponent<Transform>()->RotateXPre(0);
	spotLight.GetComponent<Transform>()->RotateZPre(0);
	spotLight.GetComponent<Transform>()->SetLocalPosition(0, 2, -2);
	spotLight.GetComponent<Light>()->type = Light::SPOT;
	spotLight.GetComponent<Light>()->SetExtra(XMFLOAT4(100, 0.97f, 0, 1));

	dirLight.Start();
	dirLight.AddComponent<Light>()->SetColor(XMFLOAT4(0, 0, 1, 1));
	dirLight.AddComponent<Transform>();
	dirLight.GetComponent<Transform>()->RotateXPre(50);
	dirLight.GetComponent<Transform>()->RotateZPre(-15);
	dirLight.GetComponent<Transform>()->SetLocalPosition(4, 3, -2);
	dirLight.GetComponent<Light>()->type = Light::DIRECTIONAL;
	dirLight.GetComponent<Light>()->SetExtra(XMFLOAT4(100, 0.97f, 0, 1));

	prefabTest.AddComponent<PrefabLoader>()->Load("test.prefab");
}

void GameObjectManager::Update()
{
	//Rotate light
	spotLight.GetComponent<Transform>()->RotateYPost(Time::Delta() * 100);

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
	spotLight.Update();
	dirLight.Update();
	button.Update();
	skybox.Update();
}

void GameObjectManager::OnDelete()
{
	cube.OnDelete();
	text.OnDelete();
	cam.OnDelete();
	prefabTest.OnDelete();
	button.OnDelete();
	spotLight.OnDelete();
	dirLight.OnDelete();
	button.OnDelete();
	skybox.OnDelete();
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
	text.GetComponent<MeshRenderer>()->SetMeshColor(XMFLOAT4(1, color, color, 1));
	color = 1 - color;
}