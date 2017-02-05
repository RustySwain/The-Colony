#include "TextRenderer.h"
#include "MeshRenderer.h"

TextRenderer::TextRenderer()
{
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::Start()
{
	gameObject->GetComponent<MeshRenderer>()->SetType(MeshRenderer::TEXT);
}

void TextRenderer::Update()
{
}

void TextRenderer::OnDelete()
{
}

void TextRenderer::LoadFromString(string _str)
{
}

string TextRenderer::WriteToString() const
{
	return "";
}

void TextRenderer::SetText(string _text)
{
}