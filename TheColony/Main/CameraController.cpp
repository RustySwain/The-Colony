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

	// get middle of the screen
	RECT winRect = Application::GetInstance()->GetWindowRect();
	screenMiddle.x = winRect.right * 0.5f;
	screenMiddle.y = winRect.bottom * 0.5f;
	// invisible cursor
	//ShowCursor(false);
	// put cursor in the middle of the screen
	SetCursorPos((int)screenMiddle.x, (int)screenMiddle.y);
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

	float speed = Time::Delta() * 10;

	// translate based on key presses

	if (scrollUp)
	{
		if (scrollUpCount > 0)
		{
			transform->TranslatePre(XMFLOAT3(0, 0, -speed* 10));
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
	if (GetAsyncKeyState(' '))
		_cameraOrigin->TranslatePre(XMFLOAT3(0, speed, 0));
	if (GetAsyncKeyState(VK_LSHIFT))
		_cameraOrigin->TranslatePre(XMFLOAT3(0, -speed, 0));

	// save position
	XMMATRIX translated = transform->GetLocalMatrix();
	XMFLOAT4X4 f;
	XMStoreFloat4x4(&f, translated);
	XMFLOAT3 pos(f.m[3][0], f.m[3][1], f.m[3][2]);
	

	// rotate based on mouse movement
	float dx = (screenMiddle.x - newMousePos.x) * 0.5f;
	float dy = (screenMiddle.y - newMousePos.y) * 0.5f;

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		_cameraOrigin->RotateYPre((Time::Delta() * 30));
		SetCursorPos((int)screenMiddle.x, (int)screenMiddle.y);
	}
}

void CameraController::OnDelete()
{
	cameraOrigin.OnDelete();
}

void CameraController::LoadFromFile(fstream & _file)
{
}

void CameraController::LoadFromString(string _str)
{
}

string CameraController::WriteToString() const
{
	return string();
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