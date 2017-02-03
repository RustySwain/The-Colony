#include "Mesh.h"
#include "fstream"
#include "sstream"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

bool Mesh::LoadFromObj(const char* _path)
{
	// open file
	ifstream reader;
	reader.open(_path);
	if (reader.is_open())
	{
		// make vectors for vertex primitives
		vector<XMFLOAT4> verts;
		vector<XMFLOAT4> norms;
		vector<XMFLOAT4> uvs;
		vector<Vec3I> indices;
		char buffer[255];
		while (!reader.eof())
		{
			reader.getline(buffer, 255);
			stringstream lnStream(buffer);
			// read first word of the line
			string firstWord;
			lnStream >> firstWord;

			// read position info
			if (firstWord == "v")
			{
				XMFLOAT4 coords;
				lnStream >> coords.x >> coords.y >> coords.z;
				coords.w = 1;
				verts.push_back(coords);
			}
			// read normal info
			else if (firstWord == "vn")
			{
				XMFLOAT4 coords;
				lnStream >> coords.x >> coords.y >> coords.z;
				coords.w = 1;
				norms.push_back(coords);
			}
			// read uv info
			else if (firstWord == "vt")
			{
				XMFLOAT4 coords;
				lnStream >> coords.x >> coords.y >> coords.z;
				coords.y = 1 - coords.y;
				coords.w = 1;
				uvs.push_back(coords);
			}
			else if (firstWord == "f")
			{
				while (true)
				{
					// read triangulated face
					char tri[255];
					lnStream >> tri;
					stringstream ss(tri);
					string str;
					getline(ss, str, '/');
					unsigned int a = atoi(str.c_str());
					getline(ss, str, '/');
					unsigned int b = atoi(str.c_str());
					unsigned int c;
					ss >> c;
					indices.push_back(Vec3I(a, b, c));
					tris.push_back((unsigned int)indices.size() - 1);
					if (lnStream.eof())
						break;
				}
			}
		}
		reader.close();
		// push verts and indices into class
		for (unsigned int i = 0; i < indices.size(); i++)
		{
			Vertex vpc;
			vpc.position = verts[indices[i].x - 1];
			vpc.uv = uvs[indices[i].y - 1];
			vpc.normal = norms[indices[i].z - 1];
			vertices.push_back(vpc);
		}
		return true;
	}
	return false;
}

void Mesh::BuildMesh(const vector<Vertex> _vertices, const vector<unsigned int> _indices)
{
	vertices = _vertices;
	tris = _indices;
}

vector<Vertex>& Mesh::GetVertexData()
{
	return vertices;
}

const vector<unsigned int> Mesh::GetTris() const
{
	return tris;
}