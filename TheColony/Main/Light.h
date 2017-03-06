#pragma once
#include "GameObject.h"
#include "d3d11.h"
#include <DirectXMath.h>

using namespace DirectX;

// Dependencies
// Transform
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

	struct LightMatrices
	{
		XMMATRIX lightView;
		XMMATRIX lightProj;
	};

	LightType type;

	Light();
	~Light();

	virtual const unsigned int GetId() const override { return id; }
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	void SetColor(XMFLOAT4 _color);
	void SetExtra(XMFLOAT4 _extra);
	void SetLookAt(float x, float y, float z);
	void GenerateViewMatrix();
	void GenerateProjectionMatrix(float screenFar, float screenNear);
	void GenerateOrthoMatrix(float screenFar, float screenNear);

	LightBufferType GetLightBuffType() const;
	LightMatrices GetLightMatrices() const;


private:
	LightBufferType lightBuffType;
	LightMatrices lightMatrices;
	XMMATRIX _viewMatrix;
	XMMATRIX _projectionMatrix;
	XMFLOAT4 _lookAt;

};
