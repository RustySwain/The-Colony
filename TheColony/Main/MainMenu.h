#pragma once
#include "SceneABC.h"
#include "Button.h"

class MainMenu : public SceneABC
{
	float slideRatio = 0;
	GameObject* slider = nullptr;
	int slideDir = 0;

	float minX = -0.75f, maxX = 0.75f;

	//Background
	GameObject background;

	// Main
	GameObject mainParent;
	GameObject playButton;
	GameObject playButtonText;
	GameObject optionsButton;
	GameObject optionsButtonText;
	GameObject quitButton;
	GameObject quitButtonText;

	// Play
	GameObject playParent;
	GameObject newGameButton;
	GameObject newGameButtonText;
	GameObject playBackButton;
	GameObject playBackButtonText;

	// Options
	GameObject optionsParent;
	GameObject graphicsButton;
	GameObject graphicsButtonText;
	GameObject audioButton;
	GameObject audioButtonText;
	GameObject optionsBackButton;
	GameObject optionsBackButtonText;

	// Graphics
	GameObject graphicsParent;
	GameObject msaaButton;
	GameObject msaaButtonText;
	GameObject vsyncButton;
	GameObject vsyncButtonText;
	GameObject shadowsButton;
	GameObject shadowsButtonText;
	GameObject fullscreenButton;
	GameObject fullscreenButtonText;
	GameObject resolutionButton;
	GameObject resolutionButtonText;
	GameObject graphicsBackButton;
	GameObject graphicsBackButtonText;

	// Audio

	// Quit
	GameObject quitParent;
	GameObject confirmQuitButton;
	GameObject confirmQuitButtonText;
	GameObject quitBackButton;
	GameObject quitBackButtonText;

	// Main
	CallbackFunc playClick;
	CallbackFunc optionsClick;
	CallbackFunc quitClick;

	// Play
	CallbackFunc newGameClick;
	CallbackFunc playBackClick;

	// Options
	CallbackFunc graphicsClick;
	CallbackFunc audioClick;
	CallbackFunc optionsBackClick;

	// Graphics
	CallbackFunc msaaClick;
	CallbackFunc vsyncClick;
	CallbackFunc shadowsClick;
	CallbackFunc fullscreenClick;
	CallbackFunc resolutionClick;
	CallbackFunc graphicsBackClick;

	// Audio

	// Quit
	CallbackFunc confirmQuitClick;
	CallbackFunc quitBackClick;

	// Main
	void PlayClick();
	void OptionsClick();
	void QuitClick();

	// Play
	void NewGameClick();
	void PlayBackClick();

	// Options
	void GraphicsClick();
	void AudioClick();
	void OptionsBackClick();

	// Graphics
	void MsaaClick();
	void VsyncClick();
	void ShadowsClick();
	void FullscreenClick();
	void ResolutionClick();
	void GraphicsBackClick();

	// Audio

	// Quit
	void ConfirmQuitClick();
	void QuitBackClick();

	static void White(GameObject* _go);
	static void Gray(GameObject* _go);

	void SlideLeft(GameObject* _go);
	void SlideRight(GameObject* _go);

	static float Lerp(float _min, float _max, float _ratio);

public:
	MainMenu();
	virtual ~MainMenu();

	// Component
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void Init() override;
};
