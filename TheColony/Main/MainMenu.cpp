#include "MainMenu.h"
#include "Transform.h"
#include "UIRenderer.h"
#include "MeshRenderer.h"
#include "Button.h"
#include "TextRenderer.h"
#include "GameScene.h"
#include "SceneManager.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Start()
{
	SceneABC::Start();

	playButton.Start();
	playButton.SetTag("Untagged");
	playButton.AddComponent<Transform>()->SetLocalPosition(-0.25f, -1.3f, 0.1f);
	playButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	playButton.AddComponent<UIRenderer>()->SetRect(0.1f, 0.1f, 0.3f, 0.3f);
	func = [=]() -> void { Callback(); };
	playButton.AddComponent<Button>()->Subscribe(&func);

	playButtonText.Start();
	playButtonText.SetTag("Text");
	playButtonText.AddComponent <Transform>();
	playButtonText.AddComponent<MeshRenderer>();
	playButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Font.fontsheet", L"../Assets/Fonts/Font.dds");
	playButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	playButtonText.GetComponent<Transform>()->SetParent(playButton.GetComponent<Transform>());
	playButtonText.GetComponent<Transform>()->SetLocalPosition(0.1f, 0.75f, -0.1f);
	playButtonText.GetComponent<TextRenderer>()->SetText("New Game");
}

void MainMenu::Update()
{
	SceneABC::Update();
	playButton.Update();
	playButtonText.Update();
}

void MainMenu::OnDelete()
{
	SceneABC::OnDelete();
	playButton.OnDelete();
	playButtonText.OnDelete();
}

void MainMenu::Callback()
{
	gameObject->GetComponent<SceneManager>()->LoadScene<GameScene>();
}