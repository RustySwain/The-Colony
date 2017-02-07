#include "CameraController.h"
#include "Transform.h"
#include "Time.h"
#include "Application.h"

CameraController::CameraController()
{
}

CameraController::~CameraController()
{
}

void CameraController::Start()
{
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
	XMFLOAT2 newMousePos;
	POINT mP;
	GetCursorPos(&mP);
	newMousePos.x = (float)mP.x;
	newMousePos.y = (float)mP.y;

	float speed = Time::Delta();

	// translate based on key presses
	if (GetAsyncKeyState('W'))
		transform->TranslatePre(XMFLOAT3(0, 0, -speed));
	if (GetAsyncKeyState('S'))
		transform->TranslatePre(XMFLOAT3(0, 0, speed));
	if (GetAsyncKeyState('A'))
		transform->TranslatePre(XMFLOAT3(-speed, 0, 0));
	if (GetAsyncKeyState('D'))
		transform->TranslatePre(XMFLOAT3(speed, 0, 0));
	if (GetAsyncKeyState(' '))
		transform->TranslatePre(XMFLOAT3(0, speed, 0));
	if (GetAsyncKeyState(VK_LSHIFT))
		transform->TranslatePre(XMFLOAT3(0, -speed, 0));

	// save position
	XMMATRIX translated = transform->GetLocalMatrix();
	XMFLOAT4X4 f;
	XMStoreFloat4x4(&f, translated);
	XMFLOAT3 pos(f.m[3][0], f.m[3][1], f.m[3][2]);

	// rotate based on mouse movement
	float dx = (screenMiddle.x - newMousePos.x) * 0.5f;
	float dy = (screenMiddle.y - newMousePos.y) * 0.5f;

	if (GetAsyncKeyState(VK_NUMPAD4))
	{
		transform->RotateYPost(dx);
		transform->RotateXPre(dy);
		// put camera back to saved position
		transform->SetLocalPosition(pos.x, pos.y, pos.z);
		// put cursor back in the middle of the screen
		SetCursorPos((int)screenMiddle.x, (int)screenMiddle.y);
	}
}

void CameraController::OnDelete()
{
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

void CameraController::ThirdPerson(GameObject obj, float speed)
{
}