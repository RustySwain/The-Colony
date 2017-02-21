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
	animation.CSJointsCount = 0;
	for (size_t j = 0; j < animation.GetJoints().size(); ++j)
	{
		float previousTime = animation.GetJoints()[j].keyFrames[currFrame].duration;
		XMMATRIX previousMatrix = animation.GetJoints()[j].keyFrames[currFrame].transform;
		float nextTime = animation.GetJoints()[j].keyFrames[currFrame + 1].duration;
		XMMATRIX nextMatrix = animation.GetJoints()[j].keyFrames[currFrame + 1].transform;

		/*float ratio = 0.0f;
		if (_ratio < -0.5f)
			ratio = (elapsedTime - previousTime) / (nextTime - previousTime);
		else
			ratio = _ratio;

		if (ratio < 0) ratio = 0;
		if (ratio > 1) ratio = 1;*/

		XMVECTOR scalePre, rotPre, posPre;
		XMMatrixDecompose(&scalePre, &rotPre, &posPre, previousMatrix);

		XMVECTOR scalePost, rotPost, posPost;
		XMMatrixDecompose(&scalePost, &rotPost, &posPost, nextMatrix);

		XMMATRIX interpolatedMat = XMMatrixAffineTransformation(XMVectorLerp(scalePre, scalePost, 1), XMVectorZero(), XMQuaternionSlerp(rotPre, rotPost, 1), XMVectorLerp(posPre, posPost, 1));
		XMMATRIX newPosition = animation.GetJoints()[j].world * interpolatedMat;

		// VShader Buffer
		XMMATRIX jointOffset = animation.GetJoints()[j].world * interpolatedMat;
		animation.CSJointsBuffer.jointOffsets[animation.CSJointsCount] = interpolatedMat;
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
	animation = _animation;
}

void Interpolator::SetTime(float _time)
{
	currTime = _time;
}
