#pragma once
#include "SceneABC.h"
#include "Application.h"
#include "Button.h"

class MainMenu : public SceneABC
{
	GameObject playButton;
	GameObject playButtonText;
	GameObject optionsButton;
	GameObject optionsButtonText;
	GameObject quitButton;
	GameObject quitButtonText;

	CallbackFunc playClick;
	CallbackFunc optionsClick;
	CallbackFunc quitClick;

	float color[3] = {};

	void PlayClick();
	void OptionsClick();
	void QuitClick();

public:
	MainMenu();
	virtual ~MainMenu();

	// Component
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
};
