#pragma once
#include "GameObject.h"
#include "d3d11.h"
#include <DirectXMath.h>

using namespace DirectX;

class CameraController : public Component
{
	const unsigned int id = 7;
	XMFLOAT2 screenMiddle;
	bool _keyPressed = false;
	bool _thirdPerson = false;
	unsigned int _timer = 0;
	bool _moving = false;

public:
	void ThirdPerson(GameObject obj, float speed);

public:
	CameraController();
	~CameraController();

	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual const unsigned int GetId() const override { return id; }
	virtual void LoadFromString(string _str) override;
	virtual string WriteToString() const override;
};
