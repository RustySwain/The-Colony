#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "BindPose.h"
#include "Interpolator.h"

class Animator : public Component
{
	const unsigned int id = 10;

	vector<Animation> animations;
	BindPose* bindPose;
	int defaultAnimation;
	Interpolator *interpolator;

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
	void LoadSpheres() const;
	void NextFrame() const;
	void PreviousFrame() const;

	// Accessors
	Animation GetAnimation(int _index);
	Animation GetDefaultAnimation();
};
