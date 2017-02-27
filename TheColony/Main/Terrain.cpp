#include "Terrain.h"
#include "MeshRenderer.h"
#include "DDSTextureLoader.h"
#include "Application.h"
#include "Macros.h"

void Terrain::CreateMesh() const
{
	Mesh*& mesh = gameObject->GetComponent<MeshRenderer>()->GetMesh();
	if (mesh)
	{
		delete mesh;
		mesh = nullptr;
	}
	mesh = new Mesh();
	gameObject->GetComponent<MeshRenderer>()->SetInitialized(false);
	gameObject->GetComponent<MeshRenderer>()->SetHasMesh(true);

	vector<Vertex>& verts = mesh->GetVertexData();
	vector<unsigned int>& tris = mesh->GetTris();

	float invWidth = 1.0f / width;
	float invHeight = 1.0f / height;
	for (unsigned int i = 0; i < width; i++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			Vertex v;
			v.position = XMFLOAT4((float)i, 0, (float)j, 1);
			v.uv = XMFLOAT4((float)i * invWidth, (float)j * invHeight, 0, 1);
			verts.push_back(v);
		}
	}

	for (unsigned int i = 0; i < width - 1; i++)
	{
		for (unsigned int j = 0; j < height - 1; j++)
		{
			tris.push_back((j + 0) * width + i + 0);
			tris.push_back((j + 1) * width + i + 0);
			tris.push_back((j + 0) * width + i + 1);
			tris.push_back((j + 1) * width + i + 0);
			tris.push_back((j + 1) * width + i + 1);
			tris.push_back((j + 0) * width + i + 1);
		}
	}
}

void Terrain::GenerateHeights()
{
	Mesh*& mesh = gameObject->GetComponent<MeshRenderer>()->GetMesh();
	vector<Vertex>& verts = mesh->GetVertexData();

	float amplitude = 1;
	float frequency = 1;

	for (unsigned int octave = 0; octave < octaves; octave++)
	{
		for (unsigned int i = 0; i < width; i++)
		{
			for (unsigned int j = 0; j < height; j++)
			{
				Vertex& v = verts[j * width + i];
				v.position.y += amplitude * generator.Noise(frequency * i, frequency * j);
			}
		}
		amplitude *= persistance;
		frequency *= lacunarity;
	}
	for (unsigned int i = 0; i < verts.size(); i++)
		verts[i].position.y *= scale;
}

void Terrain::CalculateNormals() const
{
	Mesh*& mesh = gameObject->GetComponent<MeshRenderer>()->GetMesh();
	vector<Vertex>& verts = mesh->GetVertexData();
	vector<unsigned int>& tris = mesh->GetTris();
	vector<XMVECTOR> triNormals;
	unsigned int normalsLength = (unsigned int)tris.size() / 3;
	triNormals.reserve(normalsLength);

	for (unsigned int i = 0; i < width - 1; i++)
	{
		for (unsigned int j = 0; j < height - 1; j++)
		{
			Vertex a1 = verts[(j + 0) * width + i + 0];
			Vertex b1 = verts[(j + 0) * width + i + 1];
			Vertex c1 = verts[(j + 1) * width + i + 0];
			Vertex a2 = verts[(j + 1) * width + i + 1];
			Vertex b2 = verts[(j + 0) * width + i + 1];
			Vertex c2 = verts[(j + 1) * width + i + 0];

			XMVECTOR vecA1 = { a1.position.x, a1.position.y, a1.position.z, 1 };
			XMVECTOR vecB1 = { b1.position.x, b1.position.y, b1.position.z, 1 };
			XMVECTOR vecC1 = { c1.position.x, c1.position.y, c1.position.z, 1 };
			XMVECTOR vecA2 = { a2.position.x, a2.position.y, a2.position.z, 1 };
			XMVECTOR vecB2 = { b2.position.x, b2.position.y, b2.position.z, 1 };
			XMVECTOR vecC2 = { c2.position.x, c2.position.y, c2.position.z, 1 };

			XMVECTOR vecA1B1 = XMVector3Normalize(vecB1 - vecA1);
			XMVECTOR vecA1C1 = XMVector3Normalize(vecC1 - vecA1);
			triNormals.push_back(XMVector3Cross(vecA1B1, vecA1C1));

			XMVECTOR vecA2C2 = XMVector3Normalize(vecC2 - vecA2);
			XMVECTOR vecA2B2 = XMVector3Normalize(vecB2 - vecA2);
			triNormals.push_back(XMVector3Cross(vecA2C2, vecA2B2));
		}
	}

	vector<vector<unsigned int>> normInds;
	for (unsigned int i = 0; i < verts.size(); i++)
		normInds.push_back(vector<unsigned int>());
	for (unsigned int i = 0; i < tris.size(); i++)
		normInds[tris[i]].push_back(i / 3);

	for (unsigned int i = 0; i < verts.size(); i++)
	{
		XMVECTOR normal = { 0 };
		for (unsigned int j = 0; j < normInds[i].size(); j++)
			normal += triNormals[normInds[i][j]];

		XMVECTOR normNormal = XMVector3Normalize(normal);
		verts[i].normal = XMFLOAT4(normNormal.m128_f32[0], normNormal.m128_f32[1], normNormal.m128_f32[2], normNormal.m128_f32[3]);
	}
}

void Terrain::GenerateTexture() const
{
	vector<Vertex>& verts = gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetVertexData();

	// Read grass and water textures
	unsigned int textureSize = texWidth * texHeight;
	ID3D11Resource* grass = nullptr;
	ID3D11Resource* water = nullptr;
	ID3D11Resource* rock = nullptr;
	ID3D11ShaderResourceView* out = nullptr;
	CreateDDSTextureFromFile(Application::GetInstance()->GetDevice(), L"../Assets/grass.dds", &grass, 0, 0, 0);
	CreateDDSTextureFromFile(Application::GetInstance()->GetDevice(), L"../Assets/water.dds", &water, 0, 0, 0);
	CreateDDSTextureFromFile(Application::GetInstance()->GetDevice(), L"../Assets/rock.dds", &rock, 0, 0, 0);
	unsigned int* colorData = new unsigned int[textureSize] {};

	// Copy old texture into new array
	unsigned int offset;
	auto context = Application::GetInstance()->GetContext();

	// grass
	D3D11_MAPPED_SUBRESOURCE grassSubresource;
	ZMem(grassSubresource);
	context->Map(grass, 0, D3D11_MAP_READ_WRITE, 0, &grassSubresource);
	unsigned int grassSize = grassSubresource.DepthPitch / sizeof(unsigned int);
	unsigned int grassHeight = grassSize / (grassSubresource.RowPitch / sizeof(unsigned int));
	unsigned int grassWidth = grassSubresource.DepthPitch / grassSubresource.RowPitch;
	unsigned int* grassData = new unsigned int[grassSize] {};
	grassSize = grassWidth * grassHeight;
	offset = grassSubresource.DepthPitch - (grassSize * 4);
	memcpy_s(grassData, sizeof(unsigned int) * grassSize, &((char*)grassSubresource.pData)[0], grassSubresource.DepthPitch - offset);
	context->Unmap(grass, 0);

	// water
	D3D11_MAPPED_SUBRESOURCE waterSubresource;
	ZMem(waterSubresource);
	context->Map(water, 0, D3D11_MAP_READ_WRITE, 0, &waterSubresource);
	unsigned int waterSize = waterSubresource.DepthPitch / sizeof(unsigned int);
	unsigned int waterHeight = waterSize / (waterSubresource.RowPitch / sizeof(unsigned int));
	unsigned int waterWidth = waterSubresource.DepthPitch / waterSubresource.RowPitch;
	unsigned int* waterData = new unsigned int[waterSize] {};
	waterSize = waterWidth * waterHeight;
	offset = waterSubresource.DepthPitch - (waterSize * 4);
	memcpy_s(waterData, sizeof(unsigned int) * waterSize, &((char*)waterSubresource.pData)[0], waterSubresource.DepthPitch - offset);
	context->Unmap(water, 0);

	// rock
	D3D11_MAPPED_SUBRESOURCE rockSubresource;
	ZMem(rockSubresource);
	context->Map(rock, 0, D3D11_MAP_READ_WRITE, 0, &rockSubresource);
	unsigned int rockSize = rockSubresource.DepthPitch / sizeof(unsigned int);
	unsigned int rockHeight = rockSize / (rockSubresource.RowPitch / sizeof(unsigned int));
	unsigned int rockWidth = rockSubresource.DepthPitch / rockSubresource.RowPitch;
	unsigned int* rockData = new unsigned int[rockSize] {};
	rockSize = rockWidth * rockHeight;
	offset = rockSubresource.DepthPitch - (rockSize * 4);
	memcpy_s(rockData, sizeof(unsigned int) * rockSize, &((char*)rockSubresource.pData)[0], rockSubresource.DepthPitch - offset);
	context->Unmap(rock, 0);

	// Tile new array into final array
	for (unsigned int i = 0; i < texWidth; i++)
	{
		for (unsigned int j = 0; j < texHeight; j++)
		{
			// Find adjacent vert heights
			unsigned int vertWidth = (unsigned int)((float)i / texWidth * width);
			unsigned int vertHeight = (unsigned int)((float)j / texHeight * height);

			unsigned int vi1 = vertWidth * height + vertHeight;
			unsigned int vi2 = ((vertWidth + 1) % width) * height + vertHeight;
			unsigned int vi3 = vertWidth * height + (vertHeight + 1) % height;
			unsigned int vi4 = ((vertWidth + 1) % width) * height + (vertHeight + 1) % height;
			float y1 = verts[vi1].position.y;
			float y2 = verts[vi2].position.y;
			float y3 = verts[vi3].position.y;
			float y4 = verts[vi4].position.y;

			// Bilinear Filtering for smoother results
			float horizontalRatio = (((float)i / texWidth) * width) - vertWidth;
			float verticalRatio = (((float)j / texHeight) * height) - vertHeight;
			float y13 = Lerp(y1, y3, verticalRatio);
			float y24 = Lerp(y2, y4, verticalRatio);
			float y = Lerp(y13, y24, horizontalRatio);

			// Is it grass or water?
			if (y < 2.2f)
			{
				colorData[j * texHeight + i] = waterData[j % waterHeight * waterHeight + i % waterWidth];
			}
			else
			{
				float ratio = (y - 2.5f) / (3.0f - 2.5f);
				if (ratio > 1) ratio = 1;
				if (ratio < 0) ratio = 0;
				colorData[j * texHeight + i] = ColorLerp(grassData[j % grassHeight * grassHeight + i % grassWidth], rockData[j % rockHeight * rockHeight + i % rockWidth], ratio);
			}
		}
	}

	// Create new texture
	ID3D11Texture2D* nuTexture = nullptr;
	D3D11_TEXTURE2D_DESC texDesc;
	ZMem(texDesc);
	texDesc.ArraySize = 1;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	texDesc.Height = texHeight;
	texDesc.Width = texWidth;
	texDesc.MipLevels = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA texColorData;
	ZMem(texColorData);
	texColorData.pSysMem = colorData;
	texColorData.SysMemPitch = sizeof(unsigned int) * texWidth;

	Application::GetInstance()->GetDevice()->CreateTexture2D(&texDesc, &texColorData, &nuTexture);
	Application::GetInstance()->GetDevice()->CreateShaderResourceView(nuTexture, 0, &out);

	// Cleanup
	delete[] colorData;
	delete[] grassData;
	delete[] waterData;
	delete[] rockData;
	SAFE_RELEASE(grass);
	SAFE_RELEASE(water);
	SAFE_RELEASE(rock);
	SAFE_RELEASE(nuTexture);

	// Set new texture
	gameObject->GetComponent<MeshRenderer>()->SetDiffuseMap(out);
}

float Terrain::Lerp(float _a, float _b, float _val)
{
	assert(_val <= 1 && _val >= 0);
	if (_a < _b)
		return _a + _val * (_b - _a);
	return _b + (1 - _val) * (_a - _b);
}

unsigned int Terrain::ColorLerp(unsigned int _a, unsigned int _b, float _ratio)
{
	assert(_ratio <= 1 && _ratio >= 0);

	unsigned char* bgra_a = (unsigned char*)&_a;
	unsigned char* bgra_b = (unsigned char*)&_b;
	unsigned char bgra_ret[4];

	for (unsigned int i = 0; i < 4; i++)
	{
		bgra_ret[i] = (unsigned char)round(Lerp(bgra_a[i], bgra_b[i], _ratio));
	}
	unsigned int* ret = (unsigned int*)&bgra_ret;
	return *ret;
}

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

void Terrain::Start()
{
}

void Terrain::Update()
{
}

void Terrain::OnDelete()
{
}

void Terrain::SetSize(unsigned int _width, unsigned int _height)
{
	width = _width;
	height = _height;
}

void Terrain::SetTextureSize(unsigned int _width, unsigned int _height)
{
	texWidth = _width;
	texHeight = _height;
}

void Terrain::Seed(unsigned int _seed)
{
	generator.ReSeed(_seed);
	seed = _seed;
}

void Terrain::Generate()
{
	CreateMesh();
	GenerateHeights();
	GenerateTexture();
	CalculateNormals();
}