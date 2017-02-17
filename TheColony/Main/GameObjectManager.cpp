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
#include "SceneManager.h"
#include "MainMenu.h"
#include "GameScene.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Start()
{
	scene.Start();
	scene.AddComponent<SceneManager>();
	scene.AddComponent<MainMenu>();

	cam.SetId(2);
	cam.SetTag("Untagged");
	cam.Start();
	cam.AddComponent<Camera>();
	cam.AddComponent<Transform>();
	cam.GetComponent<Camera>()->SetFarPlane(5000);
	cam.AddComponent<CameraController>();
	cam.GetComponent<Transform>()->SetLocalPosition(0, 10, 5);
	cam.GetComponent<Transform>()->RotateXPre(-40);
}

void GameObjectManager::Update()
{
	totalTime += Time::Delta();

	// Uncomment the next line for a sweet progress  bar
	//button.GetComponent<ProgressBar>()->SetRatio(totalTime * 0.1f);

	cam.Update();
	scene.Update();
}

void GameObjectManager::OnDelete()
{
	cam.OnDelete();
	scene.OnDelete();
}

void GameObjectManager::LoadFromFile(fstream & _file)
{
}