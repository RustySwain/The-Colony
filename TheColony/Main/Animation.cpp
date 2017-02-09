#include "Animation.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::Init(std::string _name, ANIM_TYPE _type, float _length, std::vector<Joint> _bones)
{
	name = _name;
	type = _type;
	length = _length;
	numOfJoints = _bones.size();
	joints = _bones;
}
