#include "GameObjectManager.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "CameraController.h"
#include "Camera.h"
#include "Time.h"
#include "PrefabLoader.h"
#include "UIRenderer.h"
#include "Light.h"
#include "TextRenderer.h"
#include "Skybox.h"
#include "Animator.h"
#include "Terrain.h"
#include <ctime>
#include "ProgressBar.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Start()
{
	cube.SetId(0);
	cube.SetTag("Untagged");
	cube.Start();
	cube.AddComponent<Transform>();
	cube.AddComponent<MeshRenderer>()->LoadFromObj("../Assets/cube.obj");
	cube.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/crate.dds");

	skybox.SetId(1);
	skybox.SetTag("Untagged");
	skybox.Start();
	skybox.AddComponent<Transform>()->ScalePost(2500);
	skybox.AddComponent<MeshRenderer>();
	skybox.AddComponent<Skybox>();

	cam.SetId(2);
	cam.SetTag("Untagged");
	cam.Start();
	cam.AddComponent<Camera>();
	cam.AddComponent<Transform>();
	cam.GetComponent<Camera>()->SetFarPlane(5000);
	cam.AddComponent<CameraController>();
	cam.GetComponent<Transform>()->SetLocalPosition(0, 10, 5);
	cam.GetComponent<Transform>()->RotateXPre(-40);

	button.SetId(3);
	button.SetTag("Untagged");
	button.Start();
	button.AddComponent<Transform>()->SetLocalPosition(-0.95f, -0.1f, 0.1f);
	button.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	button.AddComponent<UIRenderer>()->SetRect(0.1f, 0.1f, 0.3f, 0.3f);
	func = [=]() -> void { Callback(); };
	button.AddComponent<Button>()->Subscribe(&func);
	button.AddComponent<ProgressBar>()->SetMode(ProgressBar::FILL | ProgressBar::HORIZONTAL | ProgressBar::POSITIVE);

	text.SetId(4);
	text.SetTag("Text");
	text.Start();
	text.AddComponent <Transform>();
	text.AddComponent<MeshRenderer>();
	text.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Font.fontsheet", L"../Assets/Fonts/Font.dds");
	text.GetComponent<Transform>()->ScalePost(0.0005f);
	text.GetComponent<Transform>()->SetParent(button.GetComponent<Transform>());
	text.GetComponent<Transform>()->SetLocalPosition(0.1f, 0.75f, -0.1f);
	text.GetComponent<TextRenderer>()->SetText("Hello, World!");

	//Lighting
	spotLight.SetId(5);
	spotLight.SetTag("Untagged");
	spotLight.Start();
	spotLight.AddComponent<Light>()->SetColor(XMFLOAT4(0, 0, 1, 1));
	spotLight.AddComponent<Transform>();
	spotLight.GetComponent<Transform>()->RotateYPre(180);
	spotLight.GetComponent<Transform>()->RotateXPre(-50);
	spotLight.GetComponent<Transform>()->RotateZPre(0);
	spotLight.GetComponent<Transform>()->SetLocalPosition(0, 2, -2);
	spotLight.GetComponent<Light>()->type = Light::SPOT;
	spotLight.GetComponent<Light>()->SetExtra(XMFLOAT4(100, 0.97f, 0, 1));

	dirLight.SetId(6);
	dirLight.SetTag("Untagged");
	dirLight.Start();
	dirLight.AddComponent<Light>()->SetColor(XMFLOAT4(1, 1, 1, 1));
	dirLight.AddComponent<Transform>();
	dirLight.GetComponent<Transform>()->RotateXPre(50);
	dirLight.GetComponent<Transform>()->RotateZPre(-15);
	dirLight.GetComponent<Transform>()->SetLocalPosition(4, 3, -2);
	dirLight.GetComponent<Light>()->type = Light::DIRECTIONAL;

	pointLight.SetId(7);
	pointLight.SetTag("Untagged");
	pointLight.Start();
	pointLight.AddComponent<Light>()->SetColor(XMFLOAT4(1, 1, 1, 1));
	pointLight.AddComponent<Transform>();
	pointLight.GetComponent<Transform>()->SetLocalPosition(0, 0, 1);
	pointLight.GetComponent<Light>()->SetExtra(XMFLOAT4(3, 0, 0, 1));
	pointLight.GetComponent<Light>()->type = Light::POINT;

	// Test Objects
	//teddy.AddComponent<PrefabLoader>()->Load("../Assets/Prefabs/Teddy.prefab");
	//teddy.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/Teddy.dds");
	box.SetId(8);
	box.SetTag("Untagged");
	box.AddComponent<PrefabLoader>()->Load("../Assets/Prefabs/Box.prefab");
	//box.GetComponent<MeshRenderer>()->SetTransparent(true);
	box.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/Box.dds");
	//box.GetComponent<Animator>()->Play("Box_Idle");

	// Terrain
	terrain.SetId(9);
	terrain.SetTag("Untagged");
	terrain.Start();
	terrain.AddComponent<Transform>()->SetLocalPosition(-20, -5, -20);
	terrain.AddComponent<MeshRenderer>();// ->LoadDiffuseMap(L"../Assets/rock.dds");
	terrain.AddComponent<Terrain>()->SetSize(100, 100);
	terrain.GetComponent<Terrain>()->SetTextureSize(1000, 1000);
	terrain.GetComponent<Terrain>()->Seed(0);// (unsigned int)time(0));
	terrain.GetComponent<Terrain>()->SetOctaves(3);
	//terrain.GetComponent<Terrain>()->SetScale(0.3f);
	terrain.GetComponent<Terrain>()->SetPersistance(1.5f);
	terrain.GetComponent<Terrain>()->SetLacunarity(0.1f);
	terrain.GetComponent<Terrain>()->Generate();
}

void GameObjectManager::Update()
{
	totalTime += Time::Delta();
	//Rotate light
	spotLight.GetComponent<Transform>()->RotateYPost(Time::Delta() * 100);

	// Testing instancing stuff, feel free to remove, but it works
	static unsigned int instanceInd = 1;
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
	if (GetAsyncKeyState('L'))
		dirLight.GetComponent<Transform>()->RotateYPost(Time::Delta() * 180.0f);

	if (GetAsyncKeyState(VK_RIGHT) & 0x1)
		box.GetComponent<Animator>()->NextFrame();
	if (GetAsyncKeyState(VK_LEFT) & 0x1)
		box.GetComponent<Animator>()->PreviousFrame();

	// Uncomment the next line for a sweet progress  bar
	//button.GetComponent<ProgressBar>()->SetRatio(totalTime * 0.1f);

	cube.Update();
	text.Update();
	cam.Update();
	button.Update();
	spotLight.Update();
	dirLight.Update();
	skybox.Update();
	pointLight.Update();

	teddy.Update();
	box.Update();
	terrain.Update();
}

void GameObjectManager::OnDelete()
{
	cube.OnDelete();
	text.OnDelete();
	cam.OnDelete();
	button.OnDelete();
	spotLight.OnDelete();
	dirLight.OnDelete();
	pointLight.OnDelete();
	skybox.OnDelete();

	teddy.OnDelete();
	box.OnDelete();
	terrain.OnDelete();
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
	GameObject::FindFromTag("Text")[0]->GetComponent<MeshRenderer>()->SetMeshColor(XMFLOAT4(1, color, color, 1));
	color = 1 - color;
}