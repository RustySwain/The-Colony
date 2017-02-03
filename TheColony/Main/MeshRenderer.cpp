#include "MeshRenderer.h"
#include "Macros.h"
#include "DDSTextureLoader.h"
#include "Application.h"
#include "Transform.h"

void MeshRenderer::Init()
{
	if (initialized)
		return;
	initialized = true;
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
}

void MeshRenderer::OnDelete()
{
	if (mesh) delete mesh;
	mesh = nullptr;
	SAFE_RELEASE(vertBuffer);
	SAFE_RELEASE(indexBuffer);
	SAFE_RELEASE(constantBuffer);
	SAFE_RELEASE(diffuseMap);
	SAFE_RELEASE(normalMap);
	SAFE_RELEASE(specularMap);
	SAFE_RELEASE(emissiveMap);
	SAFE_RELEASE(sampler);
}

void MeshRenderer::LoadFromString(string _str)
{
}

bool MeshRenderer::LoadFromObj(const char* _path)
{
	if (mesh) delete mesh;
	mesh = new Mesh();
	return mesh->LoadFromObj(_path);
}

void MeshRenderer::LoadDiffuseMap(const wchar_t* _path)
{
	CreateDDSTextureFromFile(Application::GetInstance()->GetDevice(), _path, 0, &diffuseMap);
	D3D11_SAMPLER_DESC sDesc;
	ZMem(sDesc);
	sDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.MaxAnisotropy = 4;
	sDesc.MaxLOD = 100;
	sDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	Application::GetInstance()->GetDevice()->CreateSamplerState(&sDesc, &sampler);
}

void MeshRenderer::LoadNormalMap(const wchar_t* _path)
{
	CreateDDSTextureFromFile(Application::GetInstance()->GetDevice(), _path, 0, &normalMap);
}

void MeshRenderer::LoadSpecularMap(const wchar_t* _path)
{
	CreateDDSTextureFromFile(Application::GetInstance()->GetDevice(), _path, 0, &specularMap);
}

void MeshRenderer::LoadEmissiveMap(const wchar_t* _path)
{
	CreateDDSTextureFromFile(Application::GetInstance()->GetDevice(), _path, 0, &emissiveMap);
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
	if (dynamicVerts)
		context->UpdateSubresource(vertBuffer, 0, 0, mesh->GetVertexData().data(), 0, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	unsigned int offset = 0, stride = sizeof(Vertex);
	// set buffers
	context->IASetVertexBuffers(0, 1, &vertBuffer, &stride, &offset);
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

	/*if (gameObject->GetComponent<Animator>())
		gameObject->GetComponent<Animator>()->SetVSBuffer();*/

	context->DrawIndexed((UINT)mesh->GetTris().size(), 0, 0);
}