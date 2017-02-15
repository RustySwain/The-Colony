#include "MeshRenderer.h"
#include "Macros.h"
#include "DDSTextureLoader.h"
#include "Application.h"
#include "Transform.h"
#include "TextRenderer.h"
#include <fstream>

#define INSTANCE_MAX 100000
#define VERTEX_MAX 256
#define INDEX_MAX 256

void MeshRenderer::Init()
{
	if (flags & INIT)
		return;
	flags |= INIT;

	// Cleanup past memory
	SAFE_RELEASE(vertBuffer);
	SAFE_RELEASE(indexBuffer);
	SAFE_RELEASE(constantBuffer);
	SAFE_RELEASE(instanceBuffer);
	SAFE_RELEASE(sampler);

	// create vertex buffer
	D3D11_BUFFER_DESC bDesc;
	ZMem(bDesc);
	bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bDesc.ByteWidth = sizeof(mesh->GetVertexData()[0]) * (UINT)mesh->GetVertexData().size();

	D3D11_SUBRESOURCE_DATA subData;
	ZMem(subData);
	const vector<Vertex> vertVec = mesh->GetVertexData();
	const Vertex* vertArr = vertVec.data();
	subData.pSysMem = vertArr;
	Application::GetInstance()->GetDevice()->CreateBuffer(&bDesc, &subData, &vertBuffer);

	// create index buffer
	bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bDesc.ByteWidth = sizeof(mesh->GetTris()[0]) * (UINT)mesh->GetTris().size();

	const vector<unsigned int> indVec = mesh->GetTris();
	const unsigned int* indArr = indVec.data();
	subData.pSysMem = indArr;

	Application::GetInstance()->GetDevice()->CreateBuffer(&bDesc, &subData, &indexBuffer);

	// create constant buffer w/ world matrix
	cBufferData.worldMatrix = gameObject->GetComponent<Transform>()->GetWorldMatrix();
	bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bDesc.ByteWidth = sizeof(cBufferData);

	subData.pSysMem = &cBufferData;

	Application::GetInstance()->GetDevice()->CreateBuffer(&bDesc, &subData, &constantBuffer);

	// Instances
	instances.reserve(INSTANCE_MAX);
	instanceIndices.reserve(INSTANCE_MAX);
	PerInstanceVertexData pivd;
	pivd.instanceMatrix = XMMatrixIdentity();
	instances.push_back(pivd);
	instanceIndices.push_back(-1);
	bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bDesc.ByteWidth = sizeof(PerInstanceVertexData) * INSTANCE_MAX;
	bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bDesc.Usage = D3D11_USAGE_DYNAMIC;

	subData.pSysMem = instances.data();

	Application::GetInstance()->GetDevice()->CreateBuffer(&bDesc, &subData, &instanceBuffer);

	// Sampler
	D3D11_SAMPLER_DESC sDesc;
	ZMem(sDesc);
	sDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.MaxAnisotropy = 16;
	sDesc.MaxLOD = 100;
	sDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	Application::GetInstance()->GetDevice()->CreateSamplerState(&sDesc, &sampler);

	// sign me up to be rendered every frame
	Application::GetInstance()->RegisterMeshRenderer(this);
}

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Start()
{
}

void MeshRenderer::Update()
{
	Init();
	// update constant buffer
	cBufferData.worldMatrix = gameObject->GetComponent<Transform>()->GetWorldMatrix();
	Application::GetInstance()->GetContext()->UpdateSubresource(constantBuffer, 0, 0, &cBufferData, 0, 0);

	D3D11_MAPPED_SUBRESOURCE data;
	ZMem(data);
	Application::GetInstance()->GetContext()->Map(instanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	memcpy(data.pData, instances.data(), sizeof(PerInstanceVertexData) * instances.size());
	Application::GetInstance()->GetContext()->Unmap(instanceBuffer, 0);
}

void MeshRenderer::OnDelete()
{
	if (mesh) delete mesh;
	mesh = nullptr;
	SAFE_RELEASE(vertBuffer);
	SAFE_RELEASE(indexBuffer);
	SAFE_RELEASE(constantBuffer);
	SAFE_RELEASE(instanceBuffer);
	SAFE_RELEASE(diffuseMap);
	SAFE_RELEASE(normalMap);
	SAFE_RELEASE(specularMap);
	SAFE_RELEASE(emissiveMap);
	SAFE_RELEASE(sampler);
}

void MeshRenderer::LoadFromFile(fstream & _file)
{
	int meshLength;
	_file.read((char*)&meshLength, sizeof(int));
	char* mesh = new char[meshLength + 1];
	_file.read(mesh, 1);
	_file.read(mesh, meshLength);
	mesh[meshLength] = 0;
	LoadFromBinary(mesh);
	delete[] mesh;
}

void MeshRenderer::LoadFromString(string _str)
{
	unsigned int offset = 0;

	// other members
	flags = _str[offset];
	offset += sizeof(bool);
	char t = *(char*)&_str[offset];
	type = (Type)t;
	offset += sizeof(char);

	unsigned int length = 0;

	if (flags & MESH)
	{
		length = *(char*)&_str[offset];
		offset += sizeof(char);
		memcpy_s(meshPath, 256, &_str[offset], length);
		offset += length;
	}
	if (flags & DIFFUSE)
	{
		length = *(char*)&_str[offset];
		offset += sizeof(char);
		memcpy_s(diffusePath, 256, &_str[offset], length);
		offset += length;
	}

	if (flags & NORMAL)
	{
		length = *(char*)&_str[offset];
		offset += sizeof(char);
		memcpy_s(normalPath, 256, &_str[offset], length);
		offset += length;
	}

	if (flags & SPECULAR)
	{
		length = *(char*)&_str[offset];
		offset += sizeof(char);
		memcpy_s(specularPath, 256, &_str[offset], length);
		offset += length;
	}

	if (flags & EMISSIVE)
	{
		length = *(char*)&_str[offset];
		offset += sizeof(char);
		memcpy_s(emissivePath, 256, &_str[offset], length);
	}

	if (strlen(meshPath))
		LoadFromObj(meshPath);
	if (strlen(diffusePath))
		LoadDiffuseMap((wchar_t*)diffusePath);
	if (strlen(normalPath))
		LoadNormalMap((wchar_t*)normalPath);
	if (strlen(specularPath))
		LoadSpecularMap((wchar_t*)specularPath);
	if (strlen(emissivePath))
		LoadEmissiveMap((wchar_t*)emissivePath);
}

string MeshRenderer::WriteToString() const
{
	string ret = "";

	ret.append(&flags, 0, 1);
	char* t = (char*)&type;
	ret.append(t, 0, sizeof(type));

	if (flags & HAS_MESH)
	{
		size_t length = strlen(meshPath);
		ret.append((char*)&length);
		ret.append(meshPath);
	}
	if (flags & DIFFUSE)
	{
		size_t length = strlen(diffusePath);
		ret.append((char*)&length);
		ret.append(diffusePath);
	}
	if (flags & NORMAL)
	{
		size_t length = strlen(normalPath);
		ret.append((char*)&length);
		ret.append(normalPath);
	}
	if (flags & SPECULAR)
	{
		size_t length = strlen(specularPath);
		ret.append((char*)&length);
		ret.append(specularPath);
	}
	if (flags & EMISSIVE)
	{
		size_t length = strlen(emissivePath);
		ret.append((char*)&length);
		ret.append(emissivePath);
	}
	return ret;
}

void MeshRenderer::AddInstance(XMMATRIX _mat, int _key)
{
	PerInstanceVertexData pivd;
	pivd.instanceMatrix = _mat;
	instances.push_back(pivd);
	instanceIndices.push_back(_key);
}

void MeshRenderer::UpdateInstance(XMMATRIX _mat, int _key)
{
	auto iter = find(instanceIndices.begin(), instanceIndices.end(), _key);
	if (iter != instanceIndices.end())
		instances[iter - instanceIndices.begin()].instanceMatrix = _mat;
}

void MeshRenderer::RemoveInstance(int _key)
{
	auto iter = find(instanceIndices.begin(), instanceIndices.end(), _key);
	if (iter != instanceIndices.end())
	{
		instances.erase(instances.begin() + (iter - instanceIndices.begin()));
		instanceIndices.erase(iter);
	}
}

bool MeshRenderer::LoadFromObj(char* _path)
{
	if (mesh) delete mesh;
	mesh = new Mesh();
	memcpy_s(&meshPath[0], 256, _path, strlen(_path));
	flags |= HAS_MESH;
	return mesh->LoadFromObj(_path);
}

bool MeshRenderer::LoadFromBinary(char * _path)
{
	if (mesh) delete mesh;
	mesh = new Mesh();
	memcpy_s(&meshPath[0], 256, _path, strlen(_path));
	flags |= HAS_MESH;
	string diffuseMapPath;
	bool loader = mesh->LoadFromBinary(_path, diffuseMapPath);
	if (loader)
	{
		wstring wDiffuseMapPath(diffuseMapPath.size(), L'#');
		size_t outSize;
		mbstowcs_s(&outSize, &wDiffuseMapPath[0], wDiffuseMapPath.size() + 1, diffuseMapPath.c_str(), wDiffuseMapPath.size());
		//LoadDiffuseMap(wDiffuseMapPath.c_str());
	}
	return loader;
}

void MeshRenderer::LoadDiffuseMap(const wchar_t* _path)
{
	SAFE_RELEASE(diffuseMap);
	CreateDDSTextureFromFile(Application::GetInstance()->GetDevice(), _path, 0, &diffuseMap);
	char tmp[256];
	size_t len = wcslen(_path);
	wcstombs_s(&len, tmp, _path, INT_MAX);
	memcpy_s(&diffusePath[0], 256, tmp, len);
	flags |= DIFFUSE;
}

void MeshRenderer::LoadNormalMap(const wchar_t* _path)
{
	SAFE_RELEASE(normalMap);
	CreateDDSTextureFromFile(Application::GetInstance()->GetDevice(), _path, 0, &normalMap);
	char tmp[256];
	size_t len = wcslen(_path);
	wcstombs_s(&len, tmp, _path, INT_MAX);
	memcpy_s(&diffusePath[0], 256, tmp, len);
	flags |= NORMAL;
}

void MeshRenderer::LoadSpecularMap(const wchar_t* _path)
{
	SAFE_RELEASE(specularMap);
	CreateDDSTextureFromFile(Application::GetInstance()->GetDevice(), _path, 0, &specularMap);
	char tmp[256];
	size_t len = wcslen(_path);
	wcstombs_s(&len, tmp, _path, INT_MAX);
	memcpy_s(&diffusePath[0], 256, tmp, len);
	flags |= SPECULAR;
}

void MeshRenderer::LoadEmissiveMap(const wchar_t* _path)
{
	SAFE_RELEASE(emissiveMap);
	CreateDDSTextureFromFile(Application::GetInstance()->GetDevice(), _path, 0, &emissiveMap);
	char tmp[256];
	size_t len = wcslen(_path);
	wcstombs_s(&len, tmp, _path, INT_MAX);
	memcpy_s(&diffusePath[0], 256, tmp, len);
	flags |= EMISSIVE;
}

void MeshRenderer::SetDiffuseMap(ID3D11ShaderResourceView* _diffuse)
{
	SAFE_RELEASE(diffuseMap);
	diffuseMap = _diffuse;
}

void MeshRenderer::SetMeshColor(XMFLOAT4 _rgba) const
{
	vector<Vertex>& verts = mesh->GetVertexData();
	unsigned int size = (unsigned int)verts.size();
	for (size_t i = 0; i < size; ++i)
		verts[i].color = _rgba;
}

void MeshRenderer::Render() const
{
	auto context = Application::GetInstance()->GetContext();
	// only update vertex buffer if the mesh can be changed
	if (flags & DYNAMIC)
		context->UpdateSubresource(vertBuffer, 0, 0, mesh->GetVertexData().data(), 0, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	unsigned int offset[] = { 0, 0 }, stride[] = { sizeof(Vertex), sizeof(PerInstanceVertexData) };
	// set buffers
	ID3D11Buffer* vertBuffers[] = { vertBuffer, instanceBuffer };
	context->IASetVertexBuffers(0, 2, vertBuffers, stride, offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->VSSetConstantBuffers(0, 1, &constantBuffer);
	// set textures for the pixel shader
	ID3D11ShaderResourceView* textures[] = { diffuseMap, normalMap, specularMap, emissiveMap };
	context->PSSetShaderResources(0, 4, textures);
	context->PSSetSamplers(0, 1, &sampler);
	if (type == MESH)
	{
		context->PSSetShader(Application::GetInstance()->GetPSMesh(), 0, 0);
		context->VSSetShader(Application::GetInstance()->GetVSMesh(), 0, 0);
	}
	else if (type == SKYBOX)
	{
		context->PSSetShader(Application::GetInstance()->GetPSSkybox(), 0, 0);
		context->VSSetShader(Application::GetInstance()->GetVSMesh(), 0, 0);
	}
	else if (type == UI)
	{
		context->PSSetShader(Application::GetInstance()->GetPSUI(), 0, 0);
		context->VSSetShader(Application::GetInstance()->GetVSUI(), 0, 0);
	}

	/*if (gameObject->GetComponent<Animator>())
		gameObject->GetComponent<Animator>()->SetVSBuffer();*/

	context->DrawIndexedInstanced((UINT)mesh->GetTris().size(), (UINT)instances.size(), 0, 0, 0);
}