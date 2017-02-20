#include "BindPose.h"

BindPose::BindPose()
{
}

void BindPose::Init(const int _joints, const std::vector<DirectX::XMMATRIX> _invBindPose)
{
	numOfJoints = _joints;
	invBindPose = _invBindPose;
}
