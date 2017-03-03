#pragma once
#include "DirectXMath.h"
#include "Mesh.h"

struct AABB
{
	XMFLOAT3 min = XMFLOAT3(0, 0, 0);
	XMFLOAT3 max = XMFLOAT3(0, 0, 0);
};

struct Triangle
{
	Vertex a, b, c;
	XMVECTOR centroid;
};

struct TriangleSet
{
	Mesh* mesh = nullptr;
	vector<Triangle> tris;
	vector<unsigned int> triIndices;
};

class BoundingVolumeHeirarchy
{
	struct Node
	{
		AABB bounds;
		TriangleSet triSet;
		Node* parent = nullptr;
		Node* left = nullptr;
		Node* right = nullptr;

		void Analyze(TriangleSet _triSet, unsigned int& _count, unsigned int _minimumTris);
		bool RayCast(XMFLOAT3& _outPos, float& _outDistance, XMFLOAT3 _rayStart, XMFLOAT3 _rayNormal);
		void Shutdown() const;
	};

	Node* root = nullptr;
	unsigned int count;

	static XMFLOAT3 AverageVert(TriangleSet _triSet);
	static AABB MakeAABBFromVerts(TriangleSet _triSet);
	static int PointToPlane(XMFLOAT3 _normal, float _offset, XMFLOAT3 _point);
	static float Dot(XMFLOAT3 _a, XMFLOAT3 _b);
	static bool RayToTriangle(XMFLOAT3& _outPos, float& _outDistance, XMFLOAT4 _a, XMFLOAT4 _b, XMFLOAT4 _c, XMFLOAT3 _rayStart, XMFLOAT3 _rayNormal);
	static TriangleSet CreateTriangleSet(Mesh* _mesh);
	static bool RayToAABB(AABB _aabb, XMFLOAT3 _rayStart, XMFLOAT3 _rayNormal);

public:
	BoundingVolumeHeirarchy();
	~BoundingVolumeHeirarchy();

	void Analyze(Mesh* _mesh, unsigned int _minimumTris, XMMATRIX _worldMat);
	bool RayCast(XMFLOAT3& _outPos, float& _outDistance, XMFLOAT3 _rayStart, XMFLOAT3 _rayNormal) const;
};
