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
	elapsed = 0;
}

CameraController::~CameraController()
{
}

void CameraController::Start()
{
	cameraOrigin.Start();
	gameObject->GetComponent<Transform>()->SetParent(cameraOrigin.AddComponent<Transform>());
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
		if (scrollUpCount > 0)
		{
			transform->TranslatePre(XMFLOAT3(0, 0, -speed * 10));
			scrollUpCount--;
		}
		else
		{
			scrollUp = false;
		}
	}
	if (scrollDown)
	{
		transform->TranslatePre(XMFLOAT3(0, 0, speed * 10));
		scrollDown = false;
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
	float dx = (prevFrameMousePos.x - newMousePos.x) * 0.5f;
	float dy = (prevFrameMousePos.y - newMousePos.y) * 0.5f;

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		if (dx > 0 || newMousePos.x == Application::GetInstance()->GetWindowRect().left)
		{

			_cameraOrigin->RotateYPre((Time::Delta() * 130));
		}
		else if (dx < 0 || newMousePos.x == Application::GetInstance()->GetWindowRect().right - 1)
		{

			_cameraOrigin->RotateYPre((Time::Delta() * -130));
		}

	}

	GetCursorPos(&mP);
	prevFrameMousePos = mP;
}

void CameraController::OnDelete()
{
	cameraOrigin.OnDelete();
}

void CameraController::LoadFromFile(fstream & _file)
{
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

void CameraController::ThirdPerson(GameObject obj, float speed)
{
}