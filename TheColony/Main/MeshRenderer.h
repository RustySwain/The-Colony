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

struct PerInstanceVertexData
{
	XMMATRIX instanceMatrix;
};

// Dependencies: Transform
class MeshRenderer : public Component
{
	enum Flags { INIT = 1, TRANSPRENT = 2, DYNAMIC = 4, HAS_MESH = 8, DIFFUSE = 16, NORMAL = 32, SPECULAR = 64, EMISSIVE = 128 };
	const unsigned int id = 6;

	char flags = 0;

	PerModelVertexData cBufferData;
	Mesh* mesh = nullptr;
	ID3D11Buffer* vertBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;
	ID3D11Buffer* constantBuffer = nullptr;
	ID3D11Buffer* instanceBuffer = nullptr;
	ID3D11ShaderResourceView* diffuseMap = nullptr;
	ID3D11ShaderResourceView* normalMap = nullptr;
	ID3D11ShaderResourceView* specularMap = nullptr;
	ID3D11ShaderResourceView* emissiveMap = nullptr;
	ID3D11SamplerState* sampler = nullptr;

	// Instancing
	vector<PerInstanceVertexData> instances;
	vector<int> instanceIndices;

	// Read/Write Paths
	char meshPath[256];
	char diffusePath[256];
	char normalPath[256];
	char specularPath[256];
	char emissivePath[256];

	void Init();

public:
	enum Type { MESH = 10, SKYBOX = 11, TEXT };

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

	bool GetTransparent() const { return (flags & TRANSPRENT) == 1; };
	void SetTransparent(const bool& _transparent) { flags ^= (-TRANSPRENT ^ flags) & (1 << (unsigned int)log((unsigned int)TRANSPRENT)); };

	bool GetDynamic() const { return (flags & DYNAMIC) == 1; };
	void SetDynamic(const bool& _dyanamic) { flags ^= (-DYNAMIC ^ flags) & (1 << (unsigned int)log((unsigned int)DYNAMIC)); };

	Mesh* GetMesh() const { return mesh; }

	// Instances
	void AddInstance(XMMATRIX _mat, int _key);
	void UpdateInstance(XMMATRIX _mat, int _key);
	void RemoveInstance(int _key);

	// Mesh
	bool LoadFromObj(char* _path);
	void LoadDiffuseMap(const wchar_t* _path);
	void LoadNormalMap(const wchar_t* _path);
	void LoadSpecularMap(const wchar_t* _path);
	void LoadEmissiveMap(const wchar_t* _path);
	void SetMeshColor(XMFLOAT4 _rgba) const;
	void Render() const;

private:
	Type type = MESH;
};
