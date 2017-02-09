#include "Terrain.h"
#include "MeshRenderer.h"

void Terrain::CreateMesh()
{
	if (meshGenerated) return;
	meshGenerated = true;
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

	for (unsigned int i = 0; i < width; i++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			Vertex v;
			v.position = XMFLOAT4((float)i, 0, (float)j, 1);
			v.uv = XMFLOAT4((float)i, (float)j, 0, 1);
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
	unsigned int normalsLength = tris.size() / 3;
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
			triNormals.push_back(XMVector3Cross(vecA1C1, vecA1B1));

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

		//XMVECTOR normNormal = XMVector3Normalize(normal);
		XMVECTOR normNormal = triNormals[normInds[i][0]];
		verts[i].normal = XMFLOAT4(normNormal.m128_f32[0], normNormal.m128_f32[1], normNormal.m128_f32[2], normNormal.m128_f32[3]);
	}
}

void Terrain::GenerateTexture()
{
	Mesh*& mesh = gameObject->GetComponent<MeshRenderer>()->GetMesh();
	vector<Vertex>& verts = mesh->GetVertexData();
	vector<unsigned int>& tris = mesh->GetTris();
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

void Terrain::LoadFromFile(fstream& _file)
{
}

void Terrain::LoadFromString(string _str)
{
}

string Terrain::WriteToString() const
{
	return "";
}

void Terrain::SetSize(unsigned int _width, unsigned int _height)
{
	width = _width;
	height = _height;
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
	CalculateNormals();
	GenerateTexture();
}