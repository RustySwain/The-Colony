#include "Terrain.h"
#include "MeshRenderer.h"

void Terrain::CreateMesh() const
{
	Mesh*& mesh = gameObject->GetComponent<MeshRenderer>()->GetMesh();
	if (!mesh)
	{
		mesh = new Mesh();
		gameObject->GetComponent<MeshRenderer>()->SetInitialized(false);
		gameObject->GetComponent<MeshRenderer>()->SetHasMesh(true);
	}

	vector<Vertex>& verts = mesh->GetVertexData();
	vector<unsigned int>& tris = mesh->GetTris();

	for (unsigned int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			Vertex v;
			v.position = XMFLOAT4(i, 0, j, 1);
			verts.push_back(v);
		}
	}

	for (unsigned int i = 0; i < width - 1; i++)
	{
		for (unsigned int j = 0; j < height - 1; j++)
		{
			tris.push_back((j + 0) * height + i + 0);
			tris.push_back((j + 0) * height + i + 1);
			tris.push_back((j + 1) * height + i + 0);
			tris.push_back((j + 1) * height + i + 0);
			tris.push_back((j + 0) * height + i + 1);
			tris.push_back((j + 1) * height + i + 1);
		}
	}
}

void Terrain::GenerateHeights()
{
}

void Terrain::CalculateNormals()
{
}

void Terrain::GenerateTexture()
{
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
}