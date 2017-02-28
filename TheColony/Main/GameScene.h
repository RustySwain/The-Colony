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
	GameObject gameController;

	// test objects
	GameObject bunny;
	GameObject box;
	GameObject helicopter;
	GameObject heli_prop1;
	GameObject heli_prop2;
	GameObject toyota;

	GameObject debugText;
	GameObject pickingLight;
	GameObject test;

public:
	GameScene();
	virtual ~GameScene();

	// Component
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void Init() override;
};
