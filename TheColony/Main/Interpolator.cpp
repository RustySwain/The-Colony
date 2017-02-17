#include "Interpolator.h"
#include "Transform.h"
#include "Time.h"
#include "Application.h"
#include "Macros.h"

Interpolator::Interpolator()
{
	currFrame = 3;
	currTime = Time::Delta();
}

void Interpolator::Start()
{
	D3D11_BUFFER_DESC bDesc;
	ZMem(bDesc);
	bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bDesc.ByteWidth = sizeof(Animation::JointsBuffer);

	Application::GetInstance()->GetDevice()->CreateBuffer(&bDesc, nullptr, &jointsBuffer);
}

void Interpolator::Update()
{
	int totalJoints = animation.GetTotalBones();
	for (int i = 0; i < totalJoints; ++i)
	{
		XMMATRIX newPosition = animation.GetJoints()[i].keyFrames[currFrame].transform;
		spheres[i]->GetComponent<Transform>()->SetLocalMatrix(newPosition);
		spheres[i]->GetComponent<Transform>()->ScalePre(0.3f);
		spheres[i]->Update();
	}
}

void Interpolator::OnDelete()
{
	int totalJoints = (int)spheres.size();
	for (int i = 0; i < totalJoints; ++i)
	{
		spheres[i]->OnDelete();
		delete spheres[i];
	}

	SAFE_RELEASE(jointsBuffer);
}

void Interpolator::SetAnimation(const Animation _animation)
{
	animation = _animation;
}

void Interpolator::SetTime(float _time)
{
	currTime = _time;
}
