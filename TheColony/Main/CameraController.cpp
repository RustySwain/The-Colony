#include "CameraController.h"
#include "Transform.h"
#include "Time.h"
#include "Application.h"
#include "Defines.h"

int scrollCount = 0;

CameraController::CameraController()
{
}

CameraController::~CameraController()
{
}

void CameraController::Start()
{
	cameraOrigin.Start();
	gameObject->GetComponent<Transform>()->SetParent(cameraOrigin.AddComponent<Transform>());
	gameObject->GetComponent<Transform>()->GetParent()->TranslatePre(XMFLOAT3(16, 5, 16));
	elapsed = 0;
	curScroll = 0;
	curVelocity = 0.0f;
	scrollMin = 0;
	scrollMax = 5;
	minTrans = 0.0f;
	maxTrans = 50.0f;
	minRot = 0.0f;
	maxRot = 60.0f;
}

void CameraController::Update()
{
	Transform* transform = gameObject->GetComponent<Transform>();
	Transform* _cameraOrigin = transform->GetParent();
	XMFLOAT2 newMousePos;
	POINT mP;
	GetCursorPos(&mP);
	newMousePos.x = (float)mP.x;
	newMousePos.y = (float)mP.y;

	float speed = Time::Delta() * 20;

	//Catching scroll values
	desiredScroll -= scrollCount;
	if (desiredScroll < scrollMin)
	{
		desiredScroll = scrollMin;
	}

	if (desiredScroll > scrollMax)
	{
		desiredScroll = scrollMax;
	}

	scrollCount = 0;

	curScroll = SmoothDamp(curScroll, desiredScroll, curVelocity, 0.5f, 20.0f, Time::Delta());

	float inv = maxTrans / scrollMax;
	float invAngle = maxRot / scrollMax;
	float val = curScroll * (inv)+(inv);
	float rot = curScroll * (invAngle)+(invAngle);

	transform->SetLocalMatrix(XMMatrixIdentity());
	transform->RotateXPre(-rot);
	transform->TranslatePre(XMFLOAT3(0, 0, val));

	if (GetAsyncKeyState('W'))
		_cameraOrigin->TranslatePre(XMFLOAT3(0, 0, -speed));
	if (GetAsyncKeyState('S'))
		_cameraOrigin->TranslatePre(XMFLOAT3(0, 0, speed));
	if (GetAsyncKeyState('A'))
		_cameraOrigin->TranslatePre(XMFLOAT3(-speed, 0, 0));
	if (GetAsyncKeyState('D'))
		_cameraOrigin->TranslatePre(XMFLOAT3(speed, 0, 0));

	// save position
	XMMATRIX translated = transform->GetLocalMatrix();
	XMFLOAT4X4 f;
	XMStoreFloat4x4(&f, translated);
	XMFLOAT3 pos(f.m[3][0], f.m[3][1], f.m[3][2]);

	// rotate based on mouse movement
	float dx = (prevFrameMousePos.x - newMousePos.x);
	float dy = (prevFrameMousePos.y - newMousePos.y);

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		if (dx > 0 || newMousePos.x == Application::GetInstance()->GetWindowRect().left)
		{
			_cameraOrigin->RotateYPre((dx * DPI));
		}
		else if (dx < 0 || newMousePos.x == Application::GetInstance()->GetWindowRect().right - 1)
		{
			_cameraOrigin->RotateYPre((dx * DPI));
		}
	}

	GetCursorPos(&mP);
	prevFrameMousePos = mP;
}

void CameraController::OnDelete()
{
	cameraOrigin.OnDelete();
}

float CameraController::lerp(float point1, float point2, float alpha)
{
	return point1 + alpha * (point2 - point1);
}

float CameraController::xLerp(float mMin, float mMax, float mFactor)
{
	ASSERT(0 <= mFactor && mFactor <= 1);
	float a = mMax - mMin;
	return a * sin(mFactor * XM_PI) + mMin;
}

float CameraController::SmoothDamp(float current, float target, float &currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
	smoothTime = max(0.0001f, smoothTime);
	float num = 2.0f / smoothTime;
	float num2 = num * deltaTime;
	float num3 = 1.0f / (1.0f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
	float num4 = current - target;
	float num5 = target;
	float num6 = maxSpeed * smoothTime;
	if (num4 > num6)
	{
		num4 = num6;
	}
	if (num4 < -num6)
	{
		num4 = -num6;
	}
	target = current - num4;
	float num7 = (currentVelocity + num * num4) * deltaTime;
	currentVelocity = (currentVelocity - num * num7) * num3;
	float num8 = target + (num4 + num7) * num3;
	if (num5 - current > 0.0f == num8 > num5)
	{
		num8 = num5;
		currentVelocity = (num8 - num5) / deltaTime;
	}
	return num8;
}

void CameraController::ThirdPerson(GameObject obj, float speed)
{
}