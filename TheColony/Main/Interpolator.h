#pragma once
#include "Animation.h"
#include "GameObject.h"
#include <d3d11.h>

class Interpolator
{
	Animation animation;
	float currTime;
	int currFrame;
	ID3D11Buffer *jointsBuffer = nullptr;

public:
	Interpolator(){}
	~Interpolator(){}

	void Start();
	void Update();
	void OnDelete();
	int& CurrentFrame() { return currFrame; }

	// Accessors
	float GetTime() const { return currTime; }
	Animation GetAnimation() const { return animation; }

	// Mutators
	void SetVSBuffer() const;
	void SetAnimation(const Animation _animations);
	void SetTime(float _time);
};
