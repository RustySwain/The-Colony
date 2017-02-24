#pragma once
#include <vector>
#include <DirectXMath.h>

class BindPose
{
	int numOfJoints;
	std::vector<DirectX::XMMATRIX> invBindPose;
	
public:
	BindPose(){}
	~BindPose(){}

	void Init(const int _joints, const std::vector<DirectX::XMMATRIX> _invBindPose);

	// Accessors
	std::vector<DirectX::XMMATRIX> GetBindPose() const { return invBindPose; }
	int GetNumOfJoints() const { return numOfJoints; }
};
