#include "Interpolator.h"

Interpolator::Interpolator()
{
	currFrame = 3;
}

void Interpolator::Update()
{
}

Joint Interpolator::GetCurrentWorld(int _index)
{
	return world[_index];
}

void Interpolator::SetAnimation(const Animation _animation)
{
	animation = _animation;
}

void Interpolator::SetTime(Time _time)
{
	currTime = _time;
}
