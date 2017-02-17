#include "MainMenu.h"
#include "Transform.h"
#include "UIRenderer.h"
#include "MeshRenderer.h"
#include "Button.h"
#include "TextRenderer.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Start()
{
	SceneManager::Start();

	playButton.Start();
	playButton.AddComponent<Transform>()->SetLocalPosition(0.95f, 0.1f, 0.1f);
	playButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	playButton.AddComponent<UIRenderer>()->SetRect(0.1f, 0.1f, 0.3f, 0.3f);
	func = [=]() -> void { Callback(); };
	playButton.AddComponent<Button>()->Subscribe(&func);

	playButtonText.Start();
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
	playButton.Update();
	playButtonText.Update();
}

void MainMenu::OnDelete()
{
	playButton.OnDelete();
	playButtonText.OnDelete();
}

void MainMenu::Callback()
{
	playButtonText.GetComponent<MeshRenderer>()->SetMeshColor(XMFLOAT4(1, color, color, 1));
	color = 1 - color;
}