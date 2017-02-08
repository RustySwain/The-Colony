#include "Button.h"
#include "Windows.h"
#include "Application.h"
#include "UIRenderer.h"

void Button::OnClick()
{
	for (size_t i = 0; i < callbacks.size(); i++)
		(*callbacks[i])();
}

Button::Button()
{
}

Button::~Button()
{
}

void Button::Start()
{
}

void Button::Update()
{
	if (!GetAsyncKeyState(VK_LBUTTON))
	{
		buttonDown = false;
		return;
	}
	if (buttonDown)
		return;
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	RECT winRect = Application::GetInstance()->GetWindowRect();
	float flCursorX = ((float)cursorPos.x / winRect.right) * 2 - 1;
	float flCursorY = ((float)cursorPos.y / winRect.bottom) * 2 - 1;
	XMFLOAT4 uiRect = gameObject->GetComponent<UIRenderer>()->GetRect();
	if (flCursorX > uiRect.y && flCursorX < uiRect.y + uiRect.w &&  -flCursorY < uiRect.x &&  -flCursorY > uiRect.x - uiRect.z)
		OnClick();
	buttonDown = true;
}

void Button::OnDelete()
{
}

void Button::LoadFromFile(fstream& _file)
{
}

void Button::LoadFromString(string _str)
{
}

string Button::WriteToString() const
{
	return "";
}

void Button::Subscribe(CallbackFunc* _callback)
{
	callbacks.push_back(_callback);
}

bool Button::Unsubscribe(CallbackFunc* _callback)
{
	for (size_t i = 0; i < callbacks.size(); i++)
	{
		if (callbacks[i])
		{
			callbacks.erase(callbacks.begin() + i);
			return true;
		}
	}
	return false;
}