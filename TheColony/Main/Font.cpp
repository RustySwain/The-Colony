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
			left -= 2;
			unsigned int right = left + nuPair.second.pixelWidth;
			nuPair.second.pixelHeight = charBottom - charTop;

			nuPair.second.top = (float)charTop / textureHeight;
			nuPair.second.bottom = (float)(charBottom + charTop) / textureHeight;
			nuPair.second.left = (float)left / textureWidth;
			nuPair.second.right = (float)right / textureWidth;
			nuPair.second.key = nuPair.first;

			characters.insert(nuPair);
		}
		reader.close();
		pair<char, RendereredCharacter> nuPair;
		nuPair.second = characters.begin()._Ptr->_Myval.second;
		nuPair.first = ' ';
		nuPair.second.key = nuPair.first;
		nuPair.second.top = 0;
		nuPair.second.bottom = 0;
		nuPair.second.left = 0;
		nuPair.second.right = 0;
		characters.insert(nuPair);

		return true;
	}
	return false;
}

Font::Font()
{
}

Font::~Font()
{
}

bool Font::LoadFromFile(const char* _fontsheetPath)
{
	if (!LoadFontSheet(_fontsheetPath))
		return false;
	return true;
}

const RendereredCharacter Font::GetChar(char _char)
{
	return characters[_char];
}