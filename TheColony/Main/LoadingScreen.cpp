#include "LoadingScreen.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "TextRenderer.h"

LoadingScreen::LoadingScreen()
{
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::Start()
{
	text.Start();
	text.AddComponent<Transform>();
	text.AddComponent<MeshRenderer>();
	text.AddComponent<TextRenderer>()->SetFont("../Assets/Fonts/Agency_FB/Agency_FB.fontsheet", L"../Assets/Fonts/Agency_FB/Agency_FB.dds");
	text.GetComponent<TextRenderer>()->SetText("");
}

void LoadingScreen::Update()
{
	text.Update();
}

void LoadingScreen::OnDelete()
{
	text.OnDelete();
}

void LoadingScreen::SetText(string _message)
{
	text.GetComponent<TextRenderer>()->SetText(_message);
}