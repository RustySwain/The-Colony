#pragma once
#include "GameObject.h"
#include "Font.h"

// Dependencies
// MeshRenderer
class TextRenderer : public Component
{
	const unsigned int id = 13;
	Font* font;

public:
	TextRenderer();
	~TextRenderer();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromString(string _str) override;
	virtual string WriteToString() const override;

	void SetText(string _text);
};
