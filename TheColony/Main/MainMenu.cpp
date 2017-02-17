#include "MainMenu.h"
#include "Transform.h"
#include "UIRenderer.h"
#include "MeshRenderer.h"
#include "Button.h"
#include "TextRenderer.h"
#include "GameScene.h"
#include "SceneManager.h"

void MainMenu::PlayClick()
{
	playButtonText.GetComponent<MeshRenderer>()->SetMeshColor(XMFLOAT4(1, color[0], color[0], 1));
	color[0] = 1 - color[0];
	gameObject->GetComponent<SceneManager>()->LoadScene<GameScene>();
}

void MainMenu::OptionsClick()
{
	optionsButtonText.GetComponent<MeshRenderer>()->SetMeshColor(XMFLOAT4(1, color[1], color[1], 1));
	color[1] = 1 - color[1];
}

void MainMenu::QuitClick()
{
	quitButtonText.GetComponent<MeshRenderer>()->SetMeshColor(XMFLOAT4(1, color[2], color[2], 1));
	color[2] = 1 - color[2];
}

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Start()
{
	// Play
	playButton.Start();
	playButton.AddComponent<Transform>()->SetLocalPosition(0, 0, 0.1f);
	playButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	playButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	playClick = [=]() -> void { PlayClick(); };
	playButton.AddComponent<Button>()->Subscribe(&playClick);

	playButtonText.Start();
	playButtonText.SetTag("Text");
	playButtonText.AddComponent <Transform>();
	playButtonText.AddComponent<MeshRenderer>();
	playButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Font.fontsheet", L"../Assets/Fonts/Font.dds");
	playButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	playButtonText.GetComponent<Transform>()->SetParent(playButton.GetComponent<Transform>());
	playButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.35f, -0.1f);
	playButtonText.GetComponent<TextRenderer>()->SetText("Play");

	// Options
	optionsButton.Start();
	optionsButton.AddComponent<Transform>()->SetLocalPosition(0, -0.25f, 0.1f);
	optionsButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	optionsButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	optionsClick = [=]() -> void { OptionsClick(); };
	optionsButton.AddComponent<Button>()->Subscribe(&optionsClick);

	optionsButtonText.Start();
	optionsButtonText.AddComponent <Transform>();
	optionsButtonText.AddComponent<MeshRenderer>();
	optionsButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Font.fontsheet", L"../Assets/Fonts/Font.dds");
	optionsButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	optionsButtonText.GetComponent<Transform>()->SetParent(optionsButton.GetComponent<Transform>());
	optionsButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.35f, -0.1f);
	optionsButtonText.GetComponent<TextRenderer>()->SetText("Options");

	// Quit
	quitButton.Start();
	quitButton.AddComponent<Transform>()->SetLocalPosition(0, -0.5f, 0.1f);
	quitButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	quitButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	quitClick = [=]() -> void { QuitClick(); };
	quitButton.AddComponent<Button>()->Subscribe(&quitClick);

	quitButtonText.Start();
	quitButtonText.AddComponent <Transform>();
	quitButtonText.AddComponent<MeshRenderer>();
	quitButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Font.fontsheet", L"../Assets/Fonts/Font.dds");
	quitButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	quitButtonText.GetComponent<Transform>()->SetParent(quitButton.GetComponent<Transform>());
	quitButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.35f, -0.1f);
	quitButtonText.GetComponent<TextRenderer>()->SetText("Quit");
}

void MainMenu::Update()
{
	playButton.Update();
	playButtonText.Update();

	optionsButton.Update();
	optionsButtonText.Update();

	quitButton.Update();
	quitButtonText.Update();
}

void MainMenu::OnDelete()
{
	playButton.OnDelete();
	playButtonText.OnDelete();
	optionsButton.OnDelete();
	optionsButtonText.OnDelete();

	quitButton.OnDelete();
	quitButtonText.OnDelete();
}