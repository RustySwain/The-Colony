#pragma once
#include "GameObject.h"
#include "Animation.h"

class Animator : public Component
{
	const unsigned int id = 10;

	vector<Animation> animations;
	//BindPose* bindPose;
	int defaultAnimation;

public:
	Animator();
	~Animator();

	// Component
	virtual const unsigned int GetId() const override { return id; }
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromFile(fstream &_file) override;
	virtual void LoadFromString(string _str) override;
	virtual string WriteToString() const override;

	bool AddAnimation(const char * _path);
	//bool AddBinPose(const BindPose * _bindPose);
};
