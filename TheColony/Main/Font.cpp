#include "Font.h"
#include "DDSTextureLoader.h"
#include "Application.h"
#include "fstream"
#include "sstream";

bool Font::LoadFontSheet(const char* _fontName)
{
	ifstream reader;
	reader.open(_fontName);
	if (reader.is_open())
	{
		char buffer[256];
		reader.getline(buffer, 256);
		stringstream lineStream(buffer);
		lineStream >> textureWidth >> textureHeight >> charTop >> charBottom;
		while (!reader.eof())
		{
			reader.getline(buffer, 255);
			lineStream = stringstream(buffer);
			pair<char, RendereredCharacter> nuPair;
			unsigned int left;
			lineStream >> nuPair.first >> left >> nuPair.second.pixelWidth;
			unsigned int right = left + nuPair.second.pixelWidth;
			nuPair.second.pixelHeight = charBottom - charTop;

			nuPair.second.top = charTop / textureHeight;
			nuPair.second.bottom = charBottom / textureHeight;
			nuPair.second.left = left / textureWidth;
			nuPair.second.right = right / textureWidth;
			nuPair.second.key = nuPair.first;

			characters.insert(nuPair);
		}
		return true;
	}
	return false;
}

bool Font::LoadFontTexture(const wchar_t* _fontName)
{
	CreateDDSTextureFromFile(Application::GetInstance()->GetDevice(), _fontName, 0, &fontTexture);
	return fontTexture;
}

Font::Font()
{
}

Font::~Font()
{
}

bool Font::LoadFromFile(const char* _fontsheetPath, const wchar_t* _texPath)
{
	if (!LoadFontSheet(_fontsheetPath))
		return false;
	LoadFontTexture(_texPath);
	return true;
}