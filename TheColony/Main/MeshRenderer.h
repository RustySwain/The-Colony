#pragma once
#include "GameObject.h"
#include "d3d11.h"
#include <DirectXMath.h>
#include "Mesh.h"

using namespace DirectX;

struct PerModelVertexData
{
	XMMATRIX worldMatrix;
};

// Dependencies: Transform
class MeshRenderer : public Component
{
	const unsigned int id = 6;

	bool initialized = false;
	bool transparent = false;
	bool dynamicVerts = false;

	PerModelVertexData cBufferData;
	Mesh* mesh = nullptr;
	ID3D11Buffer* vertBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;
	ID3D11Buffer* constantBuffer = nullptr;
	ID3D11ShaderResourceView* diffuseMap = nullptr;
	ID3D11ShaderResourceView* normalMap = nullptr;
	ID3D11ShaderResourceView* specularMap = nullptr;
	ID3D11ShaderResourceView* emissiveMap = nullptr;
	ID3D11SamplerState* sampler = nullptr;

	void Init();

public:
	enum Type { MESH = 0, SKYBOX = 1 };

	MeshRenderer();
	~MeshRenderer();

	// Component
	virtual const unsigned int GetId() const override { return id; }
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromString(string _str) override;
	virtual string WriteToString() const override;

	// Accessors/Mutators
	Type GetType() const { return type; };
	void SetType(const Type& _type) { type = _type; };

	bool GetTransparent() const { return transparent; };
	void SetTransparent(const bool& _transparent) { transparent = _transparent; };

	bool GetDynamic() const { return dynamicVerts; };
	void SetDynamic(const bool& _dyanamic) { dynamicVerts = _dyanamic; };

	Mesh* GetMesh() const { return mesh; }

	// Mesh
	bool LoadFromObj(const char* _path);
	void LoadDiffuseMap(const wchar_t* _path);
	void LoadNormalMap(const wchar_t* _path);
	void LoadSpecularMap(const wchar_t* _path);
	void LoadEmissiveMap(const wchar_t* _path);
	void SetMeshColor(XMFLOAT4 _rgba) const;
	void Render() const;

private:
	Type type = MESH;
};
