#pragma once
#include "GameObject.h"
#include <DirectXMath.h>

// Dependencies
// MeshRenderer
class UIRenderer : public Component
{
	const unsigned int id = 14;
	float top = 0, left = 0, height = 0, width = 0;

public:
	UIRenderer();
	~UIRenderer();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromFile(fstream &_file) override;
	virtual void LoadFromString(string _str) override;
	virtual string WriteToString() const override;

	void SetRect(float _top, float _left, float _height, float _width);
	DirectX::XMFLOAT4 GetRect() const;
};
