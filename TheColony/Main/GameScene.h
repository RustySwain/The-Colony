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
	GameObject bunny;
	GameObject box;
	GameObject helicopter;
	GameObject heli_prop1;
	GameObject heli_prop2;

public:
	GameScene();
	virtual ~GameScene();

	// Component
	void Start() override;
	void Update() override;
	void OnDelete() override;
};

