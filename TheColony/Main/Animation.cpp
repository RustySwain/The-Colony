#include "Animation.h"

Animation::Animation()
{
	type = LOOP;
	numOfJoints = 0;
	duration = 0;
}

void Animation::Init(std::string _name, int _type, float _duration, std::vector<Joint> _bones)
{
	if (0 == _type)
		type = LOOP;
	else if (1 == _type)
		type = RETURN_DEFAULT;
	else if (2 == _type)
		type = RETURN_LAST;
	else
		type = RUN_ONCE;

	name = _name;
	duration = _duration;
	numOfJoints = (unsigned int)_bones.size();
	joints = _bones;
}
