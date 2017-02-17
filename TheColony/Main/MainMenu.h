#pragma once
#include "SceneABC.h"
#include "Application.h"

class MainMenu : public SceneABC
{
	GameObject playButton;
	GameObject playButtonText;

	CallbackFunc func;

	float color = 0;

public:
	MainMenu();
	virtual ~MainMenu();

	// Component
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	void Callback();
};
