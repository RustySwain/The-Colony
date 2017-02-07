#pragma once
#include "GameObject.h"
#include "Font.h"

// Dependencies
// MeshRenderer
class TextRenderer : public Component
{
	const unsigned int id = 13;
	Font* font = nullptr;
	unsigned int textLength = 0;

public:
	TextRenderer();
	~TextRenderer();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromFile(fstream &_file) override;
	virtual void LoadFromString(string _str) override;
	virtual string WriteToString() const override;

	bool SetFont(const char* _sheetPath, const wchar_t* _texPath);
	void SetText(string _text);
	ID3D11ShaderResourceView* GetTexture() const { return font->GetTexture(); };
};
