#include "CameraController.h"
#include "Transform.h"
#include "Time.h"
#include "Application.h"
#include "Defines.h"

bool scrollUp = false;
bool scrollDown = false;
int scrollUpCount = 0;
int scrollDownCount = 0;

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
	elapsed = 0;
	curScroll = 0;
	curVelocity = 1.0f;
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

	// translate based on key presses

	if (scrollUp)
	{
		if (transform->GetWorldPosition().y > 10)
		{
			transform->TranslatePre(XMFLOAT3(0, 0, -speed * 10));
			scrollUpCount--;

			transform->RotateXPre(1.4f);
		}

		scrollUp = false;
		
	}
	if (scrollDown)
	{
		if (transform->GetWorldPosition().y < 60)
		{
			scrollDownCount++;
			desiredScroll = scrollDownCount;
			float transVal = SmoothDamp(curScroll, desiredScroll, curVelocity, 0.5f, 2.0f, Time::Delta());
			float inv = 1.0f / 30;
			float val = transVal * (15.0f * inv) + (15.0f * inv);

			transform->TranslatePre(XMFLOAT3(0, 0, val));

			transform->RotateXPre(-1.4f);

			scrollDown = false;
		}
	}

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
