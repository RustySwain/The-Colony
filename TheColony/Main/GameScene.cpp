#include "GameScene.h"
#include "CameraController.h"
#include "Skybox.h"
#include "PrefabLoader.h"
#include "Terrain.h"
#include "Time.h"
#include "Light.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include <ctime>
#include "Animator.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Start()
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
	box.SetId(8);
	box.SetTag("Untagged");
	box.Start();
	box.AddComponent<Transform>()->SetLocalPosition(5, 0, 0);
	box.GetComponent<Transform>()->ScalePre(0.5f);
	box.AddComponent<MeshRenderer>()->LoadFromBinary("../Assets/Box/Box_Idle.mesh");
	box.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/Box/Box.dds");
	box.AddComponent<Animator>()->AddAnimation("../Assets/Box/Box_Idle.anim");
	box.GetComponent<Animator>()->AddAnimation("../Assets/Box/Box_Attack.anim");
	box.GetComponent<Animator>()->AddAnimation("../Assets/Box/Box_Jump.anim");
	box.GetComponent<Animator>()->AddAnimation("../Assets/Box/Box_Walk.anim");
	box.GetComponent<Animator>()->Play("Box_Idle");

	teddy.SetId(10);
	teddy.SetTag("Untagged");
	teddy.Start();
	teddy.AddComponent<Transform>()->SetLocalPosition(-10, 0, 0);
	teddy.GetComponent<Transform>()->ScalePre(0.03f);
	teddy.AddComponent<MeshRenderer>()->LoadFromBinary("../Assets/Teddy/Teddy_Idle.mesh");
	teddy.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/Teddy/Teddy_D.dds");
	teddy.AddComponent<Animator>()->AddAnimation("../Assets/Teddy/Teddy_Idle.anim");
	teddy.GetComponent<Animator>()->Play("Teddy_Idle");

	mage.SetId(11);
	mage.SetTag("Untagged");
	mage.Start();
	mage.AddComponent<Transform>()->SetLocalPosition(0, 0, -5);
	mage.AddComponent<MeshRenderer>()->LoadFromBinary("../Assets/Mage/Mage.mesh");
	mage.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/Mage/diffuse.dds");
	mage.GetComponent<MeshRenderer>()->LoadEmissiveMap(L"../Assets/Mage/emissive.dds");
	mage.GetComponent<MeshRenderer>()->LoadNormalMap(L"../Assets/Mage/normal.dds");
	mage.GetComponent<MeshRenderer>()->LoadSpecularMap(L"../Assets/Mage/specular.dds");
	mage.AddComponent<Animator>()->AddAnimation("../Assets/Mage/Idle.anim");
	mage.GetComponent<Animator>()->Play("Idle");

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
	terrain.GetComponent<Terrain>()->SetPersistance(1.5f);
	terrain.GetComponent<Terrain>()->SetLacunarity(0.1f);
	terrain.GetComponent<Terrain>()->Generate();
}

void GameScene::Update()
{
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

	if (GetAsyncKeyState(VK_RETURN))
	{
		terrain.GetComponent<Terrain>()->Seed((unsigned int)time(0));
		terrain.GetComponent<Terrain>()->Generate();
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x1)
		box.GetComponent<Animator>()->NextFrame();
	if (GetAsyncKeyState(VK_LEFT) & 0x1)
		box.GetComponent<Animator>()->PreviousFrame();
	if (GetAsyncKeyState(VK_F1))
		box.GetComponent<Animator>()->Play("Box_Idle");
	if (GetAsyncKeyState(VK_F2))
		box.GetComponent<Animator>()->Play("Box_Attack");
	if (GetAsyncKeyState(VK_F3))
		box.GetComponent<Animator>()->Play("Box_Jump");
	if (GetAsyncKeyState(VK_F4))
		box.GetComponent<Animator>()->Play("Box_Walk");

	cube.Update();
	spotLight.Update();
	dirLight.Update();
	pointLight.Update();
	skybox.Update();
	terrain.Update();
	teddy.Update();
	box.Update();
	mage.Update();
}

void GameScene::OnDelete()
{
	cube.OnDelete();
	spotLight.OnDelete();
	dirLight.OnDelete();
	pointLight.OnDelete();
	skybox.OnDelete();
	terrain.OnDelete();
	teddy.OnDelete();
	box.OnDelete();
	mage.OnDelete();
}