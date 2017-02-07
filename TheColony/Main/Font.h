#pragma once
#include <map>
#include "d3d11.h"

using namespace std;

struct RendereredCharacter
{
	float top, left, bottom, right;
	unsigned int pixelWidth, pixelHeight;
	char key;
};

class Font
{
	unsigned int textureWidth = 0;
	unsigned int textureHeight = 0;
	unsigned int charTop = 0;
	unsigned int charBottom = 0;
	map<char, RendereredCharacter> characters;
	ID3D11ShaderResourceView* fontTexture = nullptr;

	bool LoadFontSheet(const char* _fontName);
	bool LoadFontTexture(const wchar_t* _fontName);

public:
	Font();
	~Font();

	bool LoadFromFile(const char* _fontsheetPath, const wchar_t* _texPath);
	const RendereredCharacter GetChar(char _char);

	ID3D11ShaderResourceView* GetTexture() const { return fontTexture; };
};
