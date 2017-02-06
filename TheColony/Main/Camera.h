#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "d3d11.h"
#include <DirectXMath.h>

using namespace DirectX;

class Camera : public Component
{
	const unsigned int id = 4;

	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;

	float fov = 70;
	float nearPlane = 0.01f;
	float farPlane = 100.0f;

	ID3D11Buffer* constantBuffer = nullptr;
	D3D11_VIEWPORT viewport;

	void UpdateProjMat();

public:
	static Camera* mainCam;

	Camera();
	~Camera();

	//Component
	virtual const unsigned int GetId() const override { return id; }
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromFile(fstream &_file) override;
	virtual void LoadFromString(string _str) override;
	virtual string WriteToString() const override;

	ID3D11Buffer* GetConstantBuffer() const { return constantBuffer; }

	D3D11_VIEWPORT GetViewport() const { return viewport; }

	float GetFov() const { return fov; };
	float GetNearPlane() const { return nearPlane; }
	float GetFarPlane() const { return farPlane; }

	void SetFov(const float& _fov) { fov = _fov; UpdateProjMat(); }
	void SetNearPlane(const float& _dist) { nearPlane = _dist; UpdateProjMat(); };
	void SetFarPlane(const float& _dist) { farPlane = _dist; UpdateProjMat(); };
};