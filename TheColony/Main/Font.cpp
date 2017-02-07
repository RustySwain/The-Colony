#include "Font.h"
#include "DDSTextureLoader.h"
#include "Application.h"
#include "fstream"
#include "sstream"
#include "Macros.h"

bool Font::LoadFontSheet(const char* _fontName)
{
	ifstream reader;
	reader.open(_fontName);
	if (reader.is_open())
	{
		char buffer[256];
		reader.getline(buffer, 256);
		string str = buffer;
		while (str[0] < 0)
			str.erase(str.begin());
		stringstream lineStream(str.c_str());
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

			nuPair.second.top = (float)charTop / textureHeight;
			nuPair.second.bottom = (float)(charBottom + charTop) / textureHeight;
			nuPair.second.left = (float)left / textureWidth;
			nuPair.second.right = (float)right / textureWidth;
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
	return fontTexture != nullptr;
}

Font::Font()
{
}

Font::~Font()
{
	SAFE_RELEASE(fontTexture);
}

bool Font::LoadFromFile(const char* _fontsheetPath, const wchar_t* _texPath)
{
	if (!LoadFontSheet(_fontsheetPath))
		return false;
	LoadFontTexture(_texPath);
	return true;
}

const RendereredCharacter Font::GetChar(char _char)
{
	return characters[_char];
}