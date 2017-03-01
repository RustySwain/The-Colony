#include "GameScene.h"
#include "CameraController.h"
#include "Skybox.h"
#include "Terrain.h"
#include "Time.h"
#include "Light.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include <ctime>
#include "Animator.h"
#include "AudioSource.h"
#include "Collider.h"
#include "Camera.h"
#include "Debug.h"
#include "TextRenderer.h"
#include "Application.h"
#include "PlayerController.h"
#include "GameController.h"
#include "VillagerController.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Start()
{
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

	if (GetAsyncKeyState(VK_F1))
		box.GetComponent<Animator>()->Play("Box_Idle");
	if (GetAsyncKeyState(VK_F2))
		box.GetComponent<Animator>()->Play("Box_Attack");
	if (GetAsyncKeyState(VK_F3))
		box.GetComponent<Animator>()->Play("Box_Jump");
	if (GetAsyncKeyState(VK_F4))
		box.GetComponent<Animator>()->Play("Box_Walk");

	if (GetAsyncKeyState(VK_F5))
		bunny.GetComponent<Animator>()->Play("Idle");
	if (GetAsyncKeyState(VK_F6))
		bunny.GetComponent<Animator>()->Play("Run");
	if (GetAsyncKeyState(VK_F7))
		bunny.GetComponent<Animator>()->Play("Attack");

	heli_prop1.GetComponent<Transform>()->RotateYPre(Time::Delta() * 3 * 360);
	heli_prop2.GetComponent<Transform>()->RotateZPre(Time::Delta() * 7 * 360);
	//helicopter.GetComponent<Transform>()->TranslatePre(XMFLOAT3(-0.5f, 0.15f, 0));

	cube.GetComponent<Collider>()->SetMesh(cube.GetComponent<MeshRenderer>()->GetMesh());

	cube.Update();
	spotLight.Update();
	dirLight.Update();
	pointLight.Update();
	skybox.Update();
	terrain.Update();
	bunny.Update();
	box.Update();
	helicopter.Update();
	heli_prop1.Update();
	heli_prop2.Update();
	toyota.Update();

	// Picking
	POINT mousePos;
	GetCursorPos(&mousePos);
	XMFLOAT3 mouseScreen((float)mousePos.x, (float)mousePos.y, 0);
	XMFLOAT3 nearPos = Camera::mainCam->ScreenToWorldSpace(mouseScreen);
	mouseScreen.z = Camera::mainCam->GetFarPlane();
	XMFLOAT3 farPos = Camera::mainCam->ScreenToWorldSpace(mouseScreen);
	XMVECTOR nearVec = XMVectorSet(nearPos.x, nearPos.y, nearPos.z, 1);
	XMVECTOR farVec = XMVectorSet(farPos.x, farPos.y, farPos.z, 1);
	XMVECTOR vecDir = XMVector3Normalize(farVec - nearVec);
	XMFLOAT3 flDir(vecDir.m128_f32[0], vecDir.m128_f32[1], vecDir.m128_f32[2]);
	XMFLOAT3 outPos;
	GameObject* outObj;
	bool ray = Collider::RayCastAll(outPos, outObj, nearPos, flDir);
	if (ray)
	{
		//outPos = GameController::GridSquareFromTerrain(outPos);
		pickingLight.GetComponent<Transform>()->SetLocalPosition(outPos.x - flDir.x * 0.1f, outPos.y - flDir.y * 0.1f, outPos.z - flDir.z * 0.1f);
	}

	pickingLight.Update();
	debugText.Update();

	gameController.Update();
}

void GameScene::OnDelete()
{
	cube.OnDelete();
	spotLight.OnDelete();
	dirLight.OnDelete();
	pointLight.OnDelete();
	skybox.OnDelete();
	terrain.OnDelete();
	bunny.OnDelete();
	box.OnDelete();
	helicopter.OnDelete();
	heli_prop1.OnDelete();
	heli_prop2.OnDelete();
	toyota.OnDelete();

	pickingLight.OnDelete();
	debugText.OnDelete();

	gameController.OnDelete();
}

void GameScene::Init()
{
	cube.SetId(0);
	cube.SetTag("Untagged");
	cube.SetName("Cube");
	cube.Start();
	cube.AddComponent<Transform>();
	cube.AddComponent<MeshRenderer>()->LoadFromObj("../Assets/cube.obj");
	cube.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/crate.dds");
	cube.AddComponent<Collider>()->SetMesh(cube.GetComponent<MeshRenderer>()->GetMesh());

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
	box.SetName("Box");
	box.Start();
	box.AddComponent<Transform>()->SetLocalPosition(5, 0, 0);
	box.AddComponent<MeshRenderer>()->LoadFromBinary("../Assets/Box/Box_Idle.mesh");
	box.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/Box/Box.dds");
	box.AddComponent<Animator>()->AddAnimation("../Assets/Box/Box_Idle.anim");
	box.GetComponent<Animator>()->AddAnimation("../Assets/Box/Box_Attack.anim");
	box.GetComponent<Animator>()->AddAnimation("../Assets/Box/Box_Jump.anim");
	box.GetComponent<Animator>()->AddAnimation("../Assets/Box/Box_Walk.anim");
	box.GetComponent<Animator>()->Play("Box_Jump");
	box.AddComponent<Collider>()->SetMesh(box.GetComponent<MeshRenderer>()->GetMesh());

	bunny.SetId(10);
	bunny.SetName("Bunny");
	bunny.Start();
	bunny.AddComponent<Transform>()->SetLocalPosition(2, 2.4f, 3);
	bunny.GetComponent<Transform>()->ScalePre(0.4f);
	bunny.AddComponent<MeshRenderer>()->LoadFromBinary("../Assets/Bunny/Bunny.mesh");
	bunny.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/Bunny/White.dds");
	bunny.AddComponent<Animator>()->AddAnimation("../Assets/Bunny/Idle.anim");
	bunny.GetComponent<Animator>()->AddAnimation("../Assets/Bunny/Run.anim");
	bunny.GetComponent<Animator>()->AddAnimation("../Assets/Bunny/Attack.anim");
	bunny.GetComponent<Animator>()->Play("Idle");
	bunny.AddComponent<Collider>()->SetMesh(bunny.GetComponent<MeshRenderer>()->GetMesh());
	bunny.AddComponent<VillagerController>();
	bunny.GetComponent<VillagerController>()->IsMale(true);
	bunny.GetComponent<VillagerController>()->SetAge(15);

	helicopter.SetId(11);
	helicopter.SetName("Helicopter");
	helicopter.Start();
	helicopter.AddComponent<Transform>()->SetLocalPosition(60, 10, 30);
	helicopter.GetComponent<Transform>()->ScalePre(0.5f);
	helicopter.GetComponent<Transform>()->RotateZPre(15);
	helicopter.AddComponent<MeshRenderer>()->LoadFromBinary("../Assets/Helicopter/Helicopter.mesh");
	helicopter.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/Helicopter/T_Difuse_Helicopter.dds");

	heli_prop1.Start();
	heli_prop1.AddComponent<Transform>()->SetParent(helicopter.GetComponent<Transform>());
	heli_prop1.GetComponent<Transform>()->SetLocalPosition(-0.4f, 16, 0);
	heli_prop1.AddComponent<MeshRenderer>()->LoadFromBinary("../Assets/Helicopter/Helicopter_Propeller.mesh");
	heli_prop1.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/Helicopter/T_Difuse_Helicopter.dds");
	heli_prop1.AddComponent<AudioSource>()->AddAudioClip("../Assets/sounds/heli_sound1.wav");
	heli_prop1.GetComponent<AudioSource>()->Play("heli_sound1", true);

	heli_prop2.Start();
	heli_prop2.AddComponent<Transform>()->SetParent(helicopter.GetComponent<Transform>());
	heli_prop2.GetComponent<Transform>()->SetLocalPosition(35.3f, 16, 1.5);
	heli_prop2.GetComponent<Transform>()->RotateYPre(180);
	heli_prop2.AddComponent<MeshRenderer>()->LoadFromBinary("../Assets/Helicopter/Helicopter_Propeller2.mesh");
	heli_prop2.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/Helicopter/T_Difuse_Helicopter.dds");

	toyota.SetId(12);
	toyota.SetName("Toyota");
	toyota.Start();
	toyota.AddComponent<Transform>()->SetLocalPosition(-20, 0, 5);
	toyota.GetComponent<Transform>()->ScalePre(0.2f);
	toyota.AddComponent<MeshRenderer>()->LoadFromBinary("../Assets/Toyota/toyota.mesh");
	toyota.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/Toyota/diffuse.dds");
	toyota.GetComponent<MeshRenderer>()->LoadSpecularMap(L"../Assets/Toyota/specular.dds");
	toyota.GetComponent<MeshRenderer>()->LoadNormalMap(L"../Assets/Toyota/normal.dds");
	toyota.AddComponent<AudioSource>()->AddAudioClip("../Assets/sounds/car_engine.wav");
	toyota.GetComponent<AudioSource>()->Play("car_engine", true);

	// Terrain
	terrain.SetId(9);
	terrain.SetTag("Terrain");
	terrain.SetName("Terrain");
	terrain.Start();
	terrain.AddComponent<Transform>();
	terrain.AddComponent<MeshRenderer>();// ->LoadDiffuseMap(L"../Assets/rock.dds");
	terrain.AddComponent<Terrain>()->SetSize(32, 32);
	terrain.GetComponent<Terrain>()->SetTextureSize(1000, 1000);
	terrain.GetComponent<Terrain>()->Seed(0);// (unsigned int)time(0));
	terrain.GetComponent<Terrain>()->SetOctaves(3);
	terrain.GetComponent<Terrain>()->SetPersistance(1.5f);
	terrain.GetComponent<Terrain>()->SetLacunarity(0.1f);
	terrain.GetComponent<Terrain>()->Generate();
	terrain.AddComponent<Collider>()->SetMesh(terrain.GetComponent<MeshRenderer>()->GetMesh());

	debugText.Start();
	debugText.AddComponent<Transform>()->ScalePost(0.0005f);
	debugText.GetComponent<Transform>()->TranslatePost(XMFLOAT3(-1, 0, 0));
	debugText.AddComponent<MeshRenderer>();
	debugText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	debugText.GetComponent<TextRenderer>()->SetText(" ");
	//debugText.SetEnabled(false);

	pickingLight.Start();
	pickingLight.AddComponent<Light>()->SetColor(XMFLOAT4(1, -1, -1, 1));
	pickingLight.AddComponent<Transform>();
	pickingLight.GetComponent<Light>()->SetExtra(XMFLOAT4(7, 0, 0, 1));
	pickingLight.GetComponent<Light>()->type = Light::POINT;

	gameController.SetId(3);
	gameController.SetName("GameController");
	gameController.SetTag("GameController");
	gameController.Start();
	gameController.AddComponent<PlayerController>();
	gameController.AddComponent<GameController>();
}