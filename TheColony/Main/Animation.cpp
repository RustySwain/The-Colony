#include "Animation.h"

Animation::Animation()
{
	type = LOOP;
	numOfJoints = 0;
	duration = 0;
}

void Animation::Init(std::string _name, ANIM_TYPE _type, float _duration, std::vector<Joint> _bones)
{
	name = _name;
	type = _type;
	duration = _duration;
	numOfJoints = (unsigned int)_bones.size();
	joints = _bones;
}
