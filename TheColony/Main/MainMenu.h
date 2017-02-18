#pragma once
#include "SceneABC.h"
#include "Application.h"
#include "Button.h"

class MainMenu : public SceneABC
{
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

	// Quit

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

	// Quit

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

	// Quit

	static void White(GameObject* _go);
	static void Gray(GameObject* _go);

public:
	MainMenu();
	virtual ~MainMenu();

	// Component
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
};
