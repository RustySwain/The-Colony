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

	bool LoadFontSheet(const char* _fontName);

public:
	Font();
	~Font();

	bool LoadFromFile(const char* _fontsheetPath);
	const RendereredCharacter GetChar(char _char);
};
