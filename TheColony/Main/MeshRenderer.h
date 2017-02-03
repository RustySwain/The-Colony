#pragma once
#include "GameObject.h"
#include "d3d11.h"
#include <DirectXMath.h>
#include "Mesh.h"

using namespace DirectX;

struct PerModelVertexData
{
	XMMATRIX worldMat;
};

class MeshRenderer : public Component
{
	const unsigned int id = 6;

	bool initialized = false;
	bool dynamicVerts = false;

	PerModelVertexData cBufferData;
	Mesh* mesh = nullptr;
	ID3D11Buffer* vertBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;
	ID3D11Buffer* constantBuffer = nullptr;
	ID3D11ShaderResourceView* texture = nullptr;
	ID3D11ShaderResourceView* normalMap = nullptr;
	ID3D11ShaderResourceView* specularMap = nullptr;
	ID3D11ShaderResourceView* emissiveMap = nullptr;
	ID3D11SamplerState* sampler = nullptr;

public:
	enum Type { MESH = 0, SKYBOX = 1 };
	bool transparent = false;

	MeshRenderer();
	~MeshRenderer();

	// Component
	virtual const unsigned int GetId() const override { return id; }
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromString(string _str) override;

	// Accessors/Mutators

private:
	Type type;
};
