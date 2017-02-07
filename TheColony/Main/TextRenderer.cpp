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
	gameObject->GetComponent<MeshRenderer>()->SetType(MeshRenderer::UI);
	gameObject->GetComponent<MeshRenderer>()->SetDynamic(true);
}

void TextRenderer::Update()
{
}

void TextRenderer::OnDelete()
{
	if (font) delete font;
}

void TextRenderer::LoadFromFile(fstream & _file)
{
}

void TextRenderer::LoadFromString(string _str)
{
}

string TextRenderer::WriteToString() const
{
	return "";
}

bool TextRenderer::SetFont(const char* _sheetPath, const wchar_t* _texPath)
{
	if (font) delete font;
	font = new Font();
	return font->LoadFromFile(_sheetPath, _texPath);
}

void TextRenderer::SetText(string _text)
{
	Mesh*& mesh = gameObject->GetComponent<MeshRenderer>()->GetMesh();
	if (!mesh)
	{
		mesh = new Mesh();
		gameObject->GetComponent<MeshRenderer>()->SetInitialized(false);
	}
	vector<Vertex>& verts = mesh->GetVertexData();
	vector<unsigned int>& tris = mesh->GetTris();

	if (textLength != _text.length())
	{
		verts.clear();
		tris.clear();
		gameObject->GetComponent<MeshRenderer>()->SetInitialized(false);
		textLength = _text.length();

		verts.reserve(textLength * 4);
		for (int i = 0; i < textLength * 4; i++)
			verts.push_back(Vertex());
		tris.reserve(textLength * 6);
		for (int i = 0; i < textLength * 6; i++)
			tris.push_back(0);
	}
	unsigned int rightOffset = 0;
	unsigned int vertIndex = 0;
	unsigned int indIndex = 0;
	for (size_t i = 0; i < _text.length(); i++)
	{
		char key = _text[i];
		RendereredCharacter value = font->GetChar(key);

		Vertex topLeft;
		topLeft.position.x = rightOffset;
		topLeft.position.y = value.pixelHeight;
		topLeft.uv.x = value.left;
		topLeft.uv.y = value.top;

		Vertex bottomLeft;
		bottomLeft.position.x = rightOffset;
		bottomLeft.position.y = 0;
		bottomLeft.uv.x = value.left;
		bottomLeft.uv.y = value.bottom;

		rightOffset += value.pixelWidth / 2;

		Vertex topRight;
		topRight.position.x = rightOffset;
		topRight.position.y = value.pixelHeight;
		topRight.uv.x = value.right;
		topRight.uv.y = value.top;

		Vertex bottomRight;
		bottomRight.position.x = rightOffset;
		bottomRight.position.y = 0;
		bottomRight.uv.x = value.right;
		bottomRight.uv.y = value.bottom;

		verts[vertIndex++] = topLeft;
		verts[vertIndex++] = bottomLeft;
		verts[vertIndex++] = topRight;
		verts[vertIndex++] = bottomRight;

		tris[indIndex++] = vertIndex - 3;
		tris[indIndex++] = vertIndex - 4;
		tris[indIndex++] = vertIndex - 2;
		tris[indIndex++] = vertIndex - 3;
		tris[indIndex++] = vertIndex - 2;
		tris[indIndex++] = vertIndex - 1;
	}
}