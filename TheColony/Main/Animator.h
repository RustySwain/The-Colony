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
	BindPose* bindPose;
	int defaultAnimation;
	ID3D11Buffer *jointsBuffer = nullptr;
	Interpolator *interpolator;

	// Debug
	vector<GameObject*> spheres;

public:
	Animator();
	~Animator(){}

	// Component
	virtual const unsigned int GetId() const override { return id; }
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromFile(fstream &_file) override;
	virtual void LoadFromString(string _str) override{}
	virtual string WriteToString() const override { return ""; }

	bool AddAnimation(const char * _path);
	bool AddBindPose(BindPose * _bindPose);
	bool Play(const string _animationName);
	bool Play(int _animationIndex);
	void LoadSpheres();

	// Accessors
	Animation GetAnimation(int _index);
	Animation GetDefaultAnimation();
};
