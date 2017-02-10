#pragma once
#include "Animation.h"
#include "Time.h"

class Interpolator
{
	Animation animation;
	Time currTime;
	int currFrame;
	std::vector<Joint> world;

public:
	Interpolator();
	~Interpolator(){}

	void Update();

	// Accessors
	Joint GetCurrentWorld(int _index);
	Time GetTime() const { return currTime; }
	int GetCurrFrame() const { return currFrame; }

	// Mutators
	void SetAnimation(const Animation _animations);
	void SetTime(Time _time);
};
