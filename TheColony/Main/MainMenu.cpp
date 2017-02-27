#include "MainMenu.h"
#include "Transform.h"
#include "UIRenderer.h"
#include "MeshRenderer.h"
#include "Button.h"
#include "TextRenderer.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Time.h"

void MainMenu::PlayClick()
{
	playParent.SetEnabled(true);
	newGameButton.SetEnabled(true);
	newGameButtonText.SetEnabled(true);
	playBackButton.SetEnabled(true);
	playBackButtonText.SetEnabled(true);
	playButton.GetComponent<Button>()->SetEnabled(false);
	optionsButton.GetComponent<Button>()->SetEnabled(false);
	quitButton.GetComponent<Button>()->SetEnabled(false);
	Gray(&playButton);
	Gray(&playButtonText);
	Gray(&optionsButton);
	Gray(&optionsButtonText);
	Gray(&quitButton);
	Gray(&quitButtonText);
}

void MainMenu::OptionsClick()
{
	optionsParent.SetEnabled(true);
	graphicsButton.SetEnabled(true);
	graphicsButtonText.SetEnabled(true);
	audioButton.SetEnabled(true);
	audioButtonText.SetEnabled(true);
	optionsBackButton.SetEnabled(true);
	optionsBackButtonText.SetEnabled(true);
	playButton.GetComponent<Button>()->SetEnabled(false);
	optionsButton.GetComponent<Button>()->SetEnabled(false);
	quitButton.GetComponent<Button>()->SetEnabled(false);
	Gray(&playButton);
	Gray(&playButtonText);
	Gray(&optionsButton);
	Gray(&optionsButtonText);
	Gray(&quitButton);
	Gray(&quitButtonText);
}

void MainMenu::QuitClick()
{
	quitParent.SetEnabled(true);
	confirmQuitButton.SetEnabled(true);
	confirmQuitButtonText.SetEnabled(true);
	quitBackButton.SetEnabled(true);
	quitBackButtonText.SetEnabled(true);
	playButton.GetComponent<Button>()->SetEnabled(false);
	optionsButton.GetComponent<Button>()->SetEnabled(false);
	quitButton.GetComponent<Button>()->SetEnabled(false);
	Gray(&playButton);
	Gray(&playButtonText);
	Gray(&optionsButton);
	Gray(&optionsButtonText);
	Gray(&quitButton);
	Gray(&quitButtonText);
}

void MainMenu::NewGameClick()
{
	gameObject->GetComponent<SceneManager>()->LoadScene<GameScene>();
}

void MainMenu::PlayBackClick()
{
	playParent.SetEnabled(false);
	newGameButton.SetEnabled(false);
	newGameButtonText.SetEnabled(false);
	playBackButton.SetEnabled(false);
	playBackButtonText.SetEnabled(false);
	playButton.GetComponent<Button>()->SetEnabled(true);
	optionsButton.GetComponent<Button>()->SetEnabled(true);
	quitButton.GetComponent<Button>()->SetEnabled(true);
	White(&playButton);
	White(&playButtonText);
	White(&optionsButton);
	White(&optionsButtonText);
	White(&quitButton);
	White(&quitButtonText);
}

void MainMenu::GraphicsClick()
{
	graphicsParent.SetEnabled(true);
	msaaButton.SetEnabled(true);
	msaaButtonText.SetEnabled(true);
	vsyncButton.SetEnabled(true);
	vsyncButtonText.SetEnabled(true);
	graphicsBackButton.SetEnabled(true);
	graphicsBackButtonText.SetEnabled(true);
	graphicsButton.GetComponent<Button>()->SetEnabled(false);
	audioButton.GetComponent<Button>()->SetEnabled(false);
	optionsBackButton.GetComponent<Button>()->SetEnabled(false);
	Gray(&graphicsButton);
	Gray(&graphicsButtonText);
	Gray(&audioButton);
	Gray(&audioButtonText);
	Gray(&optionsBackButton);
	Gray(&optionsBackButtonText);
	mainParent.SetEnabled(false);
	playButton.SetEnabled(false);
	playButtonText.SetEnabled(false);
	optionsButton.SetEnabled(false);
	optionsButtonText.SetEnabled(false);
	quitButton.SetEnabled(false);
	quitButtonText.SetEnabled(false);
	SlideLeft(&optionsParent);
}

void MainMenu::AudioClick()
{
}

void MainMenu::OptionsBackClick()
{
	optionsParent.SetEnabled(false);
	graphicsButton.SetEnabled(false);
	graphicsButtonText.SetEnabled(false);
	audioButton.SetEnabled(false);
	audioButtonText.SetEnabled(false);
	optionsBackButton.SetEnabled(false);
	optionsBackButtonText.SetEnabled(false);
	playButton.GetComponent<Button>()->SetEnabled(true);
	optionsButton.GetComponent<Button>()->SetEnabled(true);
	quitButton.GetComponent<Button>()->SetEnabled(true);
	White(&playButton);
	White(&playButtonText);
	White(&optionsButton);
	White(&optionsButtonText);
	White(&quitButton);
	White(&quitButtonText);
}

void MainMenu::MsaaClick()
{
}

void MainMenu::VsyncClick()
{
	bool preV = Application::GetInstance()->GetVsync();
	if (preV)
		vsyncButtonText.GetComponent<TextRenderer>()->SetText("VSync Off");
	else
		vsyncButtonText.GetComponent<TextRenderer>()->SetText("VSync On");
	Application::GetInstance()->SetVsync(!preV);
}

void MainMenu::ShadowsClick()
{
}

void MainMenu::FullscreenClick()
{
}

void MainMenu::ResolutionClick()
{
}

void MainMenu::GraphicsBackClick()
{
	graphicsParent.SetEnabled(false);
	msaaButton.SetEnabled(false);
	msaaButtonText.SetEnabled(false);
	vsyncButton.SetEnabled(false);
	vsyncButtonText.SetEnabled(false);
	graphicsBackButton.SetEnabled(false);
	graphicsBackButtonText.SetEnabled(false);
	graphicsButton.GetComponent<Button>()->SetEnabled(true);
	audioButton.GetComponent<Button>()->SetEnabled(true);
	optionsBackButton.GetComponent<Button>()->SetEnabled(true);
	White(&graphicsButton);
	White(&graphicsButtonText);
	White(&audioButton);
	White(&audioButtonText);
	White(&optionsBackButton);
	White(&optionsBackButtonText);
	mainParent.SetEnabled(true);
	playButton.SetEnabled(true);
	playButtonText.SetEnabled(true);
	optionsButton.SetEnabled(true);
	optionsButtonText.SetEnabled(true);
	quitButton.SetEnabled(true);
	quitButtonText.SetEnabled(true);
	SlideRight(&optionsParent);
}

void MainMenu::ConfirmQuitClick()
{
	Application::GetInstance()->QuitGame();
}

void MainMenu::QuitBackClick()
{
	quitParent.SetEnabled(false);
	confirmQuitButton.SetEnabled(false);
	confirmQuitButtonText.SetEnabled(false);
	quitBackButton.SetEnabled(false);
	quitBackButtonText.SetEnabled(false);
	playButton.GetComponent<Button>()->SetEnabled(true);
	optionsButton.GetComponent<Button>()->SetEnabled(true);
	quitButton.GetComponent<Button>()->SetEnabled(true);
	White(&playButton);
	White(&playButtonText);
	White(&optionsButton);
	White(&optionsButtonText);
	White(&quitButton);
	White(&quitButtonText);
}

void MainMenu::White(GameObject* _go)
{
	_go->GetComponent<MeshRenderer>()->SetMeshColor(XMFLOAT4(1, 1, 1, 1));
}

void MainMenu::Gray(GameObject* _go)
{
	_go->GetComponent<MeshRenderer>()->SetMeshColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1));
}

void MainMenu::SlideLeft(GameObject* _go)
{
	slideDir = -1;
	slider = _go;
	slideRatio = 0;
}

void MainMenu::SlideRight(GameObject* _go)
{
	slideDir = 1;
	slider = _go;
	slideRatio = 0;
}

float MainMenu::Lerp(float _min, float _max, float _ratio)
{
	return _min + _ratio * (_max - _min);
}

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Start()
{
}

void MainMenu::Update()
{
	if (slider)
	{
		slideRatio += Time::Delta();
		XMFLOAT3 posPre = slider->GetComponent<Transform>()->GetWorldPosition();
		if (slideDir == -1)
			posPre.x = -Lerp(minX, maxX, slideRatio);
		else
			posPre.x = Lerp(minX, maxX, slideRatio);
		slider->GetComponent<Transform>()->SetLocalPosition(posPre.x, posPre.y, posPre.z);

		if (slideRatio >= 1)
		{
			slider = nullptr;
			slideDir = 0;
		}
	}

	// Main
	mainParent.Update();
	playButton.Update();
	playButtonText.Update();
	optionsButton.Update();
	optionsButtonText.Update();
	quitButton.Update();
	quitButtonText.Update();

	// Play
	playParent.Update();
	newGameButton.Update();
	newGameButtonText.Update();
	playBackButton.Update();
	playBackButtonText.Update();

	// Options
	optionsParent.Update();
	graphicsButton.Update();
	graphicsButtonText.Update();
	audioButton.Update();
	audioButtonText.Update();
	optionsBackButton.Update();
	optionsBackButtonText.Update();

	// Graphics
	graphicsParent.Update();
	msaaButton.Update();
	msaaButtonText.Update();
	vsyncButton.Update();
	vsyncButtonText.Update();
	graphicsBackButton.Update();
	graphicsBackButtonText.Update();

	// Quit
	quitParent.Update();
	confirmQuitButton.Update();
	confirmQuitButtonText.Update();
	quitBackButton.Update();
	quitBackButtonText.Update();
}

void MainMenu::OnDelete()
{
	// Main
	mainParent.OnDelete();
	playButton.OnDelete();
	playButtonText.OnDelete();
	optionsButton.OnDelete();
	optionsButtonText.OnDelete();
	quitButton.OnDelete();
	quitButtonText.OnDelete();

	// Play
	playParent.OnDelete();
	newGameButton.OnDelete();
	newGameButtonText.OnDelete();
	playBackButton.OnDelete();
	playBackButtonText.OnDelete();

	// Options
	optionsParent.OnDelete();
	graphicsButton.OnDelete();
	graphicsButtonText.OnDelete();
	audioButton.OnDelete();
	audioButtonText.OnDelete();
	optionsBackButton.OnDelete();
	optionsBackButtonText.OnDelete();

	// Graphics
	graphicsParent.OnDelete();
	msaaButton.OnDelete();
	msaaButtonText.OnDelete();
	vsyncButton.OnDelete();
	vsyncButtonText.OnDelete();
	graphicsBackButton.OnDelete();
	graphicsBackButtonText.OnDelete();

	// Quit
	quitParent.OnDelete();
	confirmQuitButton.OnDelete();
	confirmQuitButtonText.OnDelete();
	quitBackButton.OnDelete();
	quitBackButtonText.OnDelete();
}

void MainMenu::Init()
{
	// Main Parent
	mainParent.Start();
	mainParent.AddComponent<Transform>()->SetLocalPosition(minX, 0, 0.5f);
	mainParent.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/frame.dds");
	mainParent.AddComponent<UIRenderer>()->SetRect(0.1f, -0.3f, 0.9f, 0.6f);

	// Play
	playButton.Start();
	playButton.AddComponent<Transform>()->SetLocalPosition(0, 0, -0.1f);
	playButton.GetComponent<Transform>()->SetParent(mainParent.GetComponent<Transform>());
	playButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	playButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	playClick = [=]() -> void { PlayClick(); };
	playButton.AddComponent<Button>()->Subscribe(&playClick);

	playButtonText.Start();
	playButtonText.AddComponent <Transform>();
	playButtonText.AddComponent<MeshRenderer>();
	playButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	playButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	playButtonText.GetComponent<Transform>()->SetParent(playButton.GetComponent<Transform>());
	playButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.37f, -0.1f);
	playButtonText.GetComponent<TextRenderer>()->SetText("Play");

	// Options
	optionsButton.Start();
	optionsButton.AddComponent<Transform>()->SetLocalPosition(0, -0.25f, -0.1f);
	optionsButton.GetComponent<Transform>()->SetParent(mainParent.GetComponent<Transform>());
	optionsButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	optionsButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	optionsClick = [=]() -> void { OptionsClick(); };
	optionsButton.AddComponent<Button>()->Subscribe(&optionsClick);

	optionsButtonText.Start();
	optionsButtonText.AddComponent <Transform>();
	optionsButtonText.AddComponent<MeshRenderer>();
	optionsButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	optionsButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	optionsButtonText.GetComponent<Transform>()->SetParent(optionsButton.GetComponent<Transform>());
	optionsButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.37f, -0.1f);
	optionsButtonText.GetComponent<TextRenderer>()->SetText("Options");

	// Quit
	quitButton.Start();
	quitButton.AddComponent<Transform>()->SetLocalPosition(0, -0.5f, -0.1f);
	quitButton.GetComponent<Transform>()->SetParent(mainParent.GetComponent<Transform>());
	quitButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	quitButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	quitClick = [=]() -> void { QuitClick(); };
	quitButton.AddComponent<Button>()->Subscribe(&quitClick);

	quitButtonText.Start();
	quitButtonText.AddComponent <Transform>();
	quitButtonText.AddComponent<MeshRenderer>();
	quitButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	quitButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	quitButtonText.GetComponent<Transform>()->SetParent(quitButton.GetComponent<Transform>());
	quitButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.37f, -0.1f);
	quitButtonText.GetComponent<TextRenderer>()->SetText("Quit");

	// Play Parent
	playParent.Start();
	playParent.AddComponent<Transform>()->SetLocalPosition(maxX, 0, 0.5f);
	playParent.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/frame.dds");
	playParent.AddComponent<UIRenderer>()->SetRect(0.1f, -0.3f, 0.9f, 0.6f);
	playParent.SetEnabled(false);

	// New Game
	newGameButton.Start();
	newGameButton.AddComponent<Transform>()->SetLocalPosition(0, 0, -0.1f);
	newGameButton.GetComponent<Transform>()->SetParent(playParent.GetComponent<Transform>());
	newGameButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	newGameButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	newGameClick = [=]() -> void { NewGameClick(); };
	newGameButton.AddComponent<Button>()->Subscribe(&newGameClick);
	newGameButton.SetEnabled(false);

	newGameButtonText.Start();
	newGameButtonText.AddComponent <Transform>();
	newGameButtonText.AddComponent<MeshRenderer>();
	newGameButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	newGameButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	newGameButtonText.GetComponent<Transform>()->SetParent(newGameButton.GetComponent<Transform>());
	newGameButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.37f, -0.1f);
	newGameButtonText.GetComponent<TextRenderer>()->SetText("New Game");
	newGameButtonText.SetEnabled(false);

	// Play Back
	playBackButton.Start();
	playBackButton.AddComponent<Transform>()->SetLocalPosition(0, -0.25f, -0.1f);
	playBackButton.GetComponent<Transform>()->SetParent(playParent.GetComponent<Transform>());
	playBackButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	playBackButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	playBackClick = [=]() -> void { PlayBackClick(); };
	playBackButton.AddComponent<Button>()->Subscribe(&playBackClick);
	playBackButton.SetEnabled(false);

	playBackButtonText.Start();
	playBackButtonText.AddComponent <Transform>();
	playBackButtonText.AddComponent<MeshRenderer>();
	playBackButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	playBackButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	playBackButtonText.GetComponent<Transform>()->SetParent(playBackButton.GetComponent<Transform>());
	playBackButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.37f, -0.1f);
	playBackButtonText.GetComponent<TextRenderer>()->SetText("Back");
	playBackButtonText.SetEnabled(false);

	// Options Parent
	optionsParent.Start();
	optionsParent.AddComponent<Transform>()->SetLocalPosition(maxX, 0, 0.5f);
	optionsParent.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/frame.dds");
	optionsParent.AddComponent<UIRenderer>()->SetRect(0.1f, -0.3f, 0.9f, 0.6f);
	optionsParent.SetEnabled(false);

	// Graphics
	graphicsButton.Start();
	graphicsButton.AddComponent<Transform>()->SetLocalPosition(0, 0, -0.1f);
	graphicsButton.GetComponent<Transform>()->SetParent(optionsParent.GetComponent<Transform>());
	graphicsButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	graphicsButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	graphicsClick = [=]() -> void { GraphicsClick(); };
	graphicsButton.AddComponent<Button>()->Subscribe(&graphicsClick);
	graphicsButton.SetEnabled(false);

	graphicsButtonText.Start();
	graphicsButtonText.AddComponent <Transform>();
	graphicsButtonText.AddComponent<MeshRenderer>();
	graphicsButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	graphicsButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	graphicsButtonText.GetComponent<Transform>()->SetParent(graphicsButton.GetComponent<Transform>());
	graphicsButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.37f, -0.1f);
	graphicsButtonText.GetComponent<TextRenderer>()->SetText("Graphics");
	graphicsButtonText.SetEnabled(false);

	// Graphics Parent
	graphicsParent.Start();
	graphicsParent.AddComponent<Transform>()->SetLocalPosition(maxX, 0, 0.5f);
	graphicsParent.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/frame.dds");
	graphicsParent.AddComponent<UIRenderer>()->SetRect(0.1f, -0.3f, 0.9f, 0.6f);
	graphicsParent.SetEnabled(false);

	// MSAA
	msaaButton.Start();
	msaaButton.AddComponent<Transform>()->SetLocalPosition(0, 0, -0.1f);
	msaaButton.GetComponent<Transform>()->SetParent(graphicsParent.GetComponent<Transform>());
	msaaButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	msaaButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	msaaClick = [=]() -> void { MsaaClick(); };
	msaaButton.AddComponent<Button>()->Subscribe(&msaaClick);
	msaaButton.SetEnabled(false);

	msaaButtonText.Start();
	msaaButtonText.AddComponent <Transform>();
	msaaButtonText.AddComponent<MeshRenderer>();
	msaaButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	msaaButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	msaaButtonText.GetComponent<Transform>()->SetParent(msaaButton.GetComponent<Transform>());
	msaaButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.37f, -0.1f);
	msaaButtonText.GetComponent<TextRenderer>()->SetText("MSAA x8");
	msaaButtonText.SetEnabled(false);

	// VSync
	vsyncButton.Start();
	vsyncButton.AddComponent<Transform>()->SetLocalPosition(0, -0.25f, -0.1f);
	vsyncButton.GetComponent<Transform>()->SetParent(graphicsParent.GetComponent<Transform>());
	vsyncButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	vsyncButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	vsyncClick = [=]() -> void { VsyncClick(); };
	vsyncButton.AddComponent<Button>()->Subscribe(&vsyncClick);
	vsyncButton.SetEnabled(false);

	vsyncButtonText.Start();
	vsyncButtonText.AddComponent <Transform>();
	vsyncButtonText.AddComponent<MeshRenderer>();
	vsyncButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	vsyncButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	vsyncButtonText.GetComponent<Transform>()->SetParent(vsyncButton.GetComponent<Transform>());
	vsyncButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.37f, -0.1f);
	vsyncButtonText.GetComponent<TextRenderer>()->SetText("VSync On");
	vsyncButtonText.SetEnabled(false);

	// Graphics Back
	graphicsBackButton.Start();
	graphicsBackButton.AddComponent<Transform>()->SetLocalPosition(0, -0.5f, -0.1f);
	graphicsBackButton.GetComponent<Transform>()->SetParent(graphicsParent.GetComponent<Transform>());
	graphicsBackButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	graphicsBackButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	graphicsBackClick = [=]() -> void { GraphicsBackClick(); };
	graphicsBackButton.AddComponent<Button>()->Subscribe(&graphicsBackClick);
	graphicsBackButton.SetEnabled(false);

	graphicsBackButtonText.Start();
	graphicsBackButtonText.AddComponent <Transform>();
	graphicsBackButtonText.AddComponent<MeshRenderer>();
	graphicsBackButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	graphicsBackButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	graphicsBackButtonText.GetComponent<Transform>()->SetParent(graphicsBackButton.GetComponent<Transform>());
	graphicsBackButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.37f, -0.1f);
	graphicsBackButtonText.GetComponent<TextRenderer>()->SetText("Back");
	graphicsBackButtonText.SetEnabled(false);

	// Audio
	audioButton.Start();
	audioButton.AddComponent<Transform>()->SetLocalPosition(0, -0.25f, -0.1f);
	audioButton.GetComponent<Transform>()->SetParent(optionsParent.GetComponent<Transform>());
	audioButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	audioButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	audioClick = [=]() -> void { AudioClick(); };
	audioButton.AddComponent<Button>()->Subscribe(&audioClick);
	audioButton.SetEnabled(false);

	audioButtonText.Start();
	audioButtonText.AddComponent <Transform>();
	audioButtonText.AddComponent<MeshRenderer>();
	audioButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	audioButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	audioButtonText.GetComponent<Transform>()->SetParent(audioButton.GetComponent<Transform>());
	audioButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.37f, -0.1f);
	audioButtonText.GetComponent<TextRenderer>()->SetText("Audio");
	audioButtonText.SetEnabled(false);

	// Options Back
	optionsBackButton.Start();
	optionsBackButton.AddComponent<Transform>()->SetLocalPosition(0, -0.5f, -0.1f);
	optionsBackButton.GetComponent<Transform>()->SetParent(optionsParent.GetComponent<Transform>());
	optionsBackButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	optionsBackButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	optionsBackClick = [=]() -> void { OptionsBackClick(); };
	optionsBackButton.AddComponent<Button>()->Subscribe(&optionsBackClick);
	optionsBackButton.SetEnabled(false);

	optionsBackButtonText.Start();
	optionsBackButtonText.AddComponent <Transform>();
	optionsBackButtonText.AddComponent<MeshRenderer>();
	optionsBackButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	optionsBackButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	optionsBackButtonText.GetComponent<Transform>()->SetParent(optionsBackButton.GetComponent<Transform>());
	optionsBackButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.37f, -0.1f);
	optionsBackButtonText.GetComponent<TextRenderer>()->SetText("Back");
	optionsBackButtonText.SetEnabled(false);

	// Quit Parent
	quitParent.Start();
	quitParent.AddComponent<Transform>()->SetLocalPosition(maxX, 0, 0.5f);
	quitParent.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/frame.dds");
	quitParent.AddComponent<UIRenderer>()->SetRect(0.1f, -0.3f, 0.9f, 0.6f);
	quitParent.SetEnabled(false);

	// Quit Confirm
	confirmQuitButton.Start();
	confirmQuitButton.AddComponent<Transform>()->SetLocalPosition(0, 0, -0.1f);
	confirmQuitButton.GetComponent<Transform>()->SetParent(quitParent.GetComponent<Transform>());
	confirmQuitButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	confirmQuitButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	confirmQuitClick = [=]() -> void { ConfirmQuitClick(); };
	confirmQuitButton.AddComponent<Button>()->Subscribe(&confirmQuitClick);
	confirmQuitButton.SetEnabled(false);

	confirmQuitButtonText.Start();
	confirmQuitButtonText.AddComponent <Transform>();
	confirmQuitButtonText.AddComponent<MeshRenderer>();
	confirmQuitButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	confirmQuitButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	confirmQuitButtonText.GetComponent<Transform>()->SetParent(confirmQuitButton.GetComponent<Transform>());
	confirmQuitButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.37f, -0.1f);
	confirmQuitButtonText.GetComponent<TextRenderer>()->SetText("Confirm");
	confirmQuitButtonText.SetEnabled(false);

	// Quit Confirm
	quitBackButton.Start();
	quitBackButton.AddComponent<Transform>()->SetLocalPosition(0, -0.25f, -0.1f);
	quitBackButton.GetComponent<Transform>()->SetParent(quitParent.GetComponent<Transform>());
	quitBackButton.AddComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/button.dds");
	quitBackButton.AddComponent<UIRenderer>()->SetRect(0.2f, -0.2f, 0.2f, 0.4f);
	quitBackClick = [=]() -> void { QuitBackClick(); };
	quitBackButton.AddComponent<Button>()->Subscribe(&quitBackClick);
	quitBackButton.SetEnabled(false);

	quitBackButtonText.Start();
	quitBackButtonText.AddComponent <Transform>();
	quitBackButtonText.AddComponent<MeshRenderer>();
	quitBackButtonText.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	quitBackButtonText.GetComponent<Transform>()->ScalePost(0.0005f);
	quitBackButtonText.GetComponent<Transform>()->SetParent(quitBackButton.GetComponent<Transform>());
	quitBackButtonText.GetComponent<Transform>()->SetLocalPosition(-0.15f, -0.37f, -0.1f);
	quitBackButtonText.GetComponent<TextRenderer>()->SetText("Back");
	quitBackButtonText.SetEnabled(false);
}