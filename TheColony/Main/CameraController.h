#pragma once
#include "GameObject.h"
#include "d3d11.h"
#include <DirectXMath.h>

#define ASSERT(bool)

using namespace DirectX;

// Dependencies
// Camera
class CameraController : public Component
{
	const unsigned int id = 7;
	bool _keyPressed = false;
	bool _thirdPerson = false;
	unsigned int _timer = 0;
	bool _moving = false;
	float elapsed;
	float start = 0.0f;
	POINT prevFrameMousePos;

	GameObject cameraOrigin;

public:
	void ThirdPerson(GameObject obj, float speed);

public:
	CameraController();
	~CameraController();

	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual const unsigned int GetId() const override { return id; }

private:
	float lerp(float point1, float point2, float alpha);
	float xLerp(float mMin, float mMax, float mFactor);
};
