#pragma once
#include "SceneManager.h"
class MainMenu : public SceneManager
{
	GameObject playButton;
	GameObject playButtonText;

	float color = 0;

public:
	MainMenu();
	virtual ~MainMenu();

	// Component
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void Callback() override;
};
