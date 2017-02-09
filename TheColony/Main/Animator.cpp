#include "Animator.h"
#include <fstream>
#include "Macros.h"
#include "Application.h"

Animator::Animator()
{
	bindPose = new BindPose();
	interpolator = new Interpolator();
	defaultAnimation = 0;
}

void Animator::Start()
{
	D3D11_BUFFER_DESC bDesc;
	ZMem(bDesc);
	bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bDesc.ByteWidth = sizeof(Animation::JointsBuffer);

	Application::GetInstance()->GetDevice()->CreateBuffer(&bDesc, nullptr, &jointsBuffer);
}

void Animator::Update()
{

}

void Animator::OnDelete()
{
	delete bindPose;
	delete interpolator;

	SAFE_RELEASE(jointsBuffer);
}

void Animator::LoadFromFile(fstream & _file)
{
	int numAnimations = 0;
	_file.read((char*)&numAnimations, sizeof(int));
	for(int i = 0; i < numAnimations; ++i)
	{
		int animLength;
		_file.read((char*)&animLength, sizeof(int));
		char* animation = new char[animLength + 1];
		_file.read(animation, 1);
		_file.read(animation, animLength);
		animation[animLength] = 0;

		string animPath = "../Assets/";
		animPath.append(animation);
		AddAnimation(animPath.c_str());
		delete[] animation;
	}
	_file.read((char*)&defaultAnimation, sizeof(int));
	int i = 0;
}

bool Animator::AddAnimation(const char * _path)
{
	fstream file;
	file.open(_path, ios_base::binary | ios_base::in);

	if(file.is_open())
	{
		Animation animation;
		vector<Joint> joints;
		vector<DirectX::XMMATRIX> invWorlds;

		int numJoints = 0;
		file.read((char*)&numJoints, sizeof(int));

		for(int i = 0; i < numJoints; ++i)
		{
			Joint joint;

			// Joint ID
			file.read((char*)&joint.id, sizeof(int));

			// Joint name
			int nameLength = 0;
			file.read((char*)&nameLength, sizeof(int));
			char *name = new char[nameLength + 1];
			file.read(name, nameLength);
			joint.name = name;
			delete[] name;

			// Joint parent
			file.read((char*)&joint.parentIndex, sizeof(int));

			// Joint world matrix
			DirectX::XMFLOAT4X4 world;
			for (int x = 0; x < 4; ++x)
			{
				for (int y = 0; y < 4; ++y)
				{
					file.read((char*)&world.m[x][y], sizeof(float));
				}
			}
			joint.world = XMLoadFloat4x4(&world);

			joints.push_back(joint);

			// Inverse Matrix
			DirectX::XMMATRIX world2;
			world2 = XMLoadFloat4x4(&world);
			DirectX::XMMATRIX invWorld;
			invWorld = XMMatrixInverse(nullptr, world2);
			invWorlds.push_back(invWorld);
		}

		bindPose->Init((int)invWorlds.size(), invWorlds);

		// Animation name
		int animNameLength = 0;
		file.read((char*)&animNameLength, sizeof(int));
		char *animName = new char[animNameLength + 1];
		file.read(animName, animNameLength);

		// Animation duration
		float animDuration = 0;
		file.read((char*)&animDuration, sizeof(float));

		for(int i = 0; i < numJoints; ++i)
		{
			// Joint ID
			int jointId = 0;
			file.read((char*)&jointId, sizeof(int));

			// Joint name
			int nameLength = 0;
			file.read((char*)&nameLength, sizeof(int));
			char *name = new char[nameLength + 1];
			file.read(name, nameLength);
			delete[] name;

			// Num of frames
			int totalFrames = 0;
			file.read((char*)&totalFrames, sizeof(int));

			// Frame
			for(int f = 0; f < totalFrames; ++f)
			{
				KeyFrame keyFrame;
				// KeyFrame ID
				file.read((char*)&keyFrame.id, sizeof(int));
				// KeyFrame Duration
				file.read((char*)&keyFrame.duration, sizeof(float));
				// KeyFrame transform matrix
				DirectX::XMFLOAT4X4 transform;
				for (int x = 0; x < 4; ++x)
				{
					for (int y = 0; y < 4; ++y)
						file.read((char*)&transform.m[x][y], sizeof(float));
				}
				keyFrame.transform = XMLoadFloat4x4(&transform);
				joints[i].keyFrames.push_back(keyFrame);
			}
		}

		animation.Init(animName, ANIM_TYPE::LOOP, animDuration, joints);
		animations.push_back(animation);

		delete[] animName;

		file.close();
		return true;
	}

	return false;
}

bool Animator::AddBindPose(BindPose * _bindPose)
{
	bindPose = _bindPose;
	return true;
}

bool Animator::Play(const string _animationName)
{
	int index = -1;
	for(int i = 0; i < (int)animations.size(); ++i)
	{
		if (animations[i].GetName() == _animationName)
		{
			index = i;
			break;
		}
	}

	if (index >= 0)
	{
		interpolator->SetAnimation(animations[index]);
		return true;
	}
		
	return false;
}

bool Animator::Play(int _animationIndex)
{
	if(_animationIndex >= 0 && _animationIndex < (int)animations.size())
	{
		interpolator->SetAnimation(animations[_animationIndex]);
		return true;
	}
	
	return false;
}

Animation Animator::GetAnimation(int _index)
{
	return animations[_index];
}

Animation Animator::GetDefaultAnimation()
{
	return animations[defaultAnimation];
}
