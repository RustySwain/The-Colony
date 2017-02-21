#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "BindPose.h"
#include "Interpolator.h"
#include <d3d11.h>

class Animator : public Component
{
	const unsigned int id = 10;

	vector<Animation> animations;
	BindPose *bindPose;
	int defaultAnimation;
	Interpolator *interpolator;

public:
	Animator();
	~Animator() {}

	// Component
	const unsigned int GetId() const override { return id; }
	void Start() override;
	void Update() override;
	void OnDelete() override;
	void LoadFromFile(fstream &_file) override;

	bool AddAnimation(const char * _path);
	bool AddBindPose(BindPose * _bindPose);
	bool Play(const string _animationName);
	bool Play(int _animationIndex);
	void NextFrame() const;
	void PreviousFrame() const;
	void SetVSBuffer() const;

	// Accessors
	Animation GetAnimation(int _index);
	Animation GetDefaultAnimation();
};
