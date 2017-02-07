#pragma once
#include <DirectXMath.h>
#include <vector>

using namespace std;
using namespace DirectX;

struct Vertex
{
	XMFLOAT4 position = XMFLOAT4(0, 0, 0, 1);
	XMFLOAT4 normal = XMFLOAT4(0, 0, 1, 1);
	XMFLOAT4 uv = XMFLOAT4(0, 0, 0, 1);
	XMFLOAT4 color = XMFLOAT4(1, 1, 1, 1);
	float jointIndex[4];
	float jointWeight[4];
	float flags[4] = { 0, 0, 0, 0 };
};

struct Vec3I
{
	int x, y, z;

	Vec3I() : x(0), y(0), z(0) {}
	Vec3I(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
};

class Mesh
{
	vector<Vertex> vertices;
	vector<unsigned int> tris;

public:
	Mesh();
	~Mesh();

	bool LoadFromObj(const char* _path);
	void BuildMesh(const vector<Vertex> _vertices, const vector<unsigned int> _indices);

	vector<Vertex>& GetVertexData();
	vector<unsigned int>& GetTris();
};
