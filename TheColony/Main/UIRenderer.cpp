#include "UIRenderer.h"
#include "MeshRenderer.h"

UIRenderer::UIRenderer()
{
}

UIRenderer::~UIRenderer()
{
}

void UIRenderer::Start()
{
	gameObject->GetComponent<MeshRenderer>()->SetType(MeshRenderer::UI);
}

void UIRenderer::Update()
{
}

void UIRenderer::OnDelete()
{
}

void UIRenderer::LoadFromFile(fstream& _file)
{
}

void UIRenderer::LoadFromString(string _str)
{
}

string UIRenderer::WriteToString() const
{
	return "";
}