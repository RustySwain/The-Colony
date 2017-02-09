#include "BindPose.h"

BindPose::BindPose()
{
	numOfJoints = 0;
}

void BindPose::Init(const int _joints, const std::vector<DirectX::XMMATRIX> _invBindPose)
{
	numOfJoints = _joints;
	invBindPose = _invBindPose;
}
