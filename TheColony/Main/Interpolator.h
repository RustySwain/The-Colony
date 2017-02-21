#pragma once
#include "Animation.h"
#include <d3d11.h>

class Interpolator
{
	Animation animation, prevAnimation, defaultAnimation;
	float currTime;
	int currFrame;
	float scale;
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
	void SetAnimation(const Animation _animation);
	void SetDefaultAnimation(const Animation _animation);
	void SetTime(float _time);
	void Scale(float _scale) { scale = _scale; }
};
