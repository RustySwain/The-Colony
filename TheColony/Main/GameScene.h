#pragma once
#include "SceneABC.h"

class GameScene : public SceneABC
{
	GameObject cube;
	GameObject spotLight;
	GameObject dirLight;
	GameObject pointLight;
	GameObject skybox;
	GameObject terrain;
	GameObject teddy;
	GameObject box;
	GameObject mage;

	//GameObject debugText;

public:
	GameScene();
	virtual ~GameScene();

	// Component
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
};
