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

bool Mesh::LoadFromBinary(const char * _path, string &_diffuseMapPath)
{
	// format path
	string path = "../Assets/";
	path.append(_path);

	fstream file;
	file.open(path, ios_base::binary | ios_base::in);
	if(file.is_open())
	{
		// has animation?
		bool hasAnimation;
		file.read((char*)&hasAnimation, sizeof(bool));

		// read diffuse map
		/*int diffuseMapLength;
		file.read((char*)&diffuseMapLength, sizeof(int));
		char* diffuseMap = new char[diffuseMapLength + 1];
		file.read(diffuseMap, diffuseMapLength);
		_diffuseMapPath = diffuseMap;*/

		// read triangles
		int numTris = 0;
		file.read((char*)&numTris, sizeof(int));
		for(int i = 0; i < numTris; ++i)
		{
			unsigned int tri1, tri2, tri3;
			file.read((char*)&tri1, sizeof(unsigned int));
			file.read((char*)&tri3, sizeof(unsigned int));
			file.read((char*)&tri2, sizeof(unsigned int));
			tris.push_back(tri1);
			tris.push_back(tri2);
			tris.push_back(tri3);
		}

		// read vertices
		int numVerts = 0;
		file.read((char*)&numVerts, sizeof(int));
		for(int i = 0; i < numVerts; ++i)
		{
			Vertex vertex;
			file.read((char*)&vertex.position, sizeof(XMFLOAT4));
			file.read((char*)&vertex.normal, sizeof(XMFLOAT4));

			if(hasAnimation)
			{
				vertex.flags[0] = 1;

				file.read((char*)&vertex.jointWeight[0], sizeof(float));
				file.read((char*)&vertex.jointWeight[1], sizeof(float));
				file.read((char*)&vertex.jointWeight[2], sizeof(float));
				file.read((char*)&vertex.jointWeight[3], sizeof(float));

				file.read((char*)&vertex.jointIndex[0], sizeof(float));
				file.read((char*)&vertex.jointIndex[1], sizeof(float));
				file.read((char*)&vertex.jointIndex[2], sizeof(float));
				file.read((char*)&vertex.jointIndex[3], sizeof(float));
			}

			file.read((char*)&vertex.uv, sizeof(XMFLOAT4));

			vertices.push_back(vertex);
		}

		file.close();
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

vector<unsigned int>& Mesh::GetTris()
{
	return tris;
}