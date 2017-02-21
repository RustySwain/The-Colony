#include "Interpolator.h"
#include "Transform.h"
#include "Time.h"
#include "Application.h"
#include "Macros.h"
#include "Animator.h"

void Interpolator::Start()
{
	currFrame = 0;
	currTime = 0;

	D3D11_BUFFER_DESC bDesc;
	ZMem(bDesc);
	bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bDesc.ByteWidth = sizeof(Animation::JointsBuffer);

	Application::GetInstance()->GetDevice()->CreateBuffer(&bDesc, nullptr, &jointsBuffer);
}

void Interpolator::Update()
{
	currTime += Time::Delta();
	while (currTime > animation.GetJoints()[0].keyFrames[currFrame].duration)
	{
		currFrame++;
		if (currFrame >= animation.GetJoints()[0].keyFrames.size() - 1)
			currTime -= animation.GetLength() - animation.GetJoints()[0].keyFrames[0].duration;
	}

	if (currFrame >= animation.GetJoints()[0].keyFrames.size() - 1)
	{
		if (animation.GetType() == RETURN_DEFAULT)
			SetAnimation(defaultAnimation);
		else if (animation.GetType() == RETURN_LAST)
			SetAnimation(prevAnimation);
		else if (animation.GetType() == RUN_ONCE)
			return;
		else
		{
			currTime = 0;
			currFrame = 0;
		}
	}

	animation.CSJointsCount = 0;
	for (size_t j = 0; j < animation.GetJoints().size(); ++j)
	{
		float previousTime = animation.GetJoints()[j].keyFrames[currFrame].duration;
		XMMATRIX previousMatrix = animation.GetJoints()[j].keyFrames[currFrame].transform;
		float nextTime = animation.GetJoints()[j].keyFrames[currFrame + 1].duration;
		XMMATRIX nextMatrix = animation.GetJoints()[j].keyFrames[currFrame + 1].transform;

		XMVECTOR scalePre, rotPre, posPre;
		XMMatrixDecompose(&scalePre, &rotPre, &posPre, previousMatrix);

		XMVECTOR scalePost, rotPost, posPost;
		XMMatrixDecompose(&scalePost, &rotPost, &posPost, nextMatrix);

		//float ratio = (currTime - previousTime) / (nextTime - previousTime);
		float ratio = 1;
		XMMATRIX interpolatedMat = XMMatrixAffineTransformation(XMVectorLerp(scalePre, scalePost, ratio), XMVectorZero(), XMQuaternionSlerp(rotPre, rotPost, ratio), XMVectorLerp(posPre, posPost, ratio));

		// VShader Buffer
		XMMATRIX jointOffset = animation.GetJoints()[j].world * interpolatedMat;
		animation.CSJointsBuffer.jointOffsets[animation.CSJointsCount] = jointOffset;
		animation.CSJointsCount += 1;
		// End VShader
	}
	Application::GetInstance()->GetContext()->UpdateSubresource(jointsBuffer, 0, nullptr, &animation.CSJointsBuffer, 0, 0);
}

void Interpolator::OnDelete()
{
	SAFE_RELEASE(jointsBuffer);
}

void Interpolator::SetVSBuffer() const
{
	Application::GetInstance()->GetContext()->VSSetConstantBuffers(2, 1, &jointsBuffer);
}

void Interpolator::SetAnimation(const Animation _animation)
{
	currTime = 0;
	currFrame = 0;

	//if (animation.GetName() == "")
		prevAnimation = defaultAnimation;
	//else
	//	prevAnimation = animation;

	animation = _animation;
}

void Interpolator::SetDefaultAnimation(const Animation _animation)
{
	defaultAnimation = _animation;
}

void Interpolator::SetTime(float _time)
{
	currTime = _time;
}
