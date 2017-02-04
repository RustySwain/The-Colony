#pragma once
#include "GameObject.h"
#include "d3d11.h"
#include <DirectXMath.h>

using namespace DirectX;

class Light : public Component
{
	const int id = 8;
public:
	enum LightType { NONE = 0, AMBIENT, DIRECTIONAL, POINT, SPOT };

	struct LightBufferType
	{
		XMFLOAT4 diffuseColor;
		XMFLOAT4 lightDirection;
		XMFLOAT4 lightPos;
		XMFLOAT4 extra;
	};

	LightType type;

	Light();
	~Light();

	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	//int GetId() const override { return id; }
	virtual const unsigned int GetId() const override { return id; }

	void SetColor(XMFLOAT4 _color);
	void SetExtra(XMFLOAT4 _extra);

	LightBufferType GetLightBuffType() const;

private:
	LightBufferType lightBuffType;
};
