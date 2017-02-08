#pragma once
#include <vector>
#include "DirectXMath.h"

struct KeyFrame
{
	int id;
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
	float length;
	std::vector<Joint> joints;

public:
	Animation();
	~Animation();

	void Init(std::string _name, ANIM_TYPE _type, float _length, std::vector<Joint> _bones);

	// Accessors
	std::string GetName() const { return name; }
	float GetLength() const { return length; }
	int GetTotalBones() const { return numOfJoints; }
	std::vector<Joint>& GetBones() { return joints; }
	ANIM_TYPE GetType() const { return type; }
};
