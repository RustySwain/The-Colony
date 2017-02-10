#pragma once
#include <vector>
#include "DirectXMath.h"

struct KeyFrame
{
	int id;
	float duration;
	DirectX::XMMATRIX transform;
};

struct Joint
{
	int id;
	std::string name;
	int parentIndex;
	DirectX::XMMATRIX world;
	std::vector<KeyFrame> keyFrames;
};

enum ANIM_TYPE { LOOP = 0, RETURN_DEFAULT, RETURN_LAST, RUN_ONCE };

class Animation
{
	std::string name;
	ANIM_TYPE type;
	unsigned int numOfJoints;
	float duration;
	std::vector<Joint> joints;

public:
	Animation();
	~Animation(){}

	// Shader
	struct JointsBuffer
	{
		DirectX::XMMATRIX jointOffsets[100];
	};
	JointsBuffer CSJointsBuffer;
	unsigned int CSJointsCount = 0;
	// End Shader

	void Init(std::string _name, ANIM_TYPE _type, float _length, std::vector<Joint> _bones);

	// Accessors
	std::string GetName() const { return name; }
	float GetLength() const { return duration; }
	int GetTotalBones() const { return numOfJoints; }
	std::vector<Joint>& GetBones() { return joints; }
	ANIM_TYPE GetType() const { return type; }
};
