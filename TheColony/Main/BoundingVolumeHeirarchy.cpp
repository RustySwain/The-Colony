#include "BoundingVolumeHeirarchy.h"

void BoundingVolumeHeirarchy::Node::Analyze(TriangleSet _triSet, unsigned int& _count, unsigned int _minimumTris)
{
	if (_triSet.triIndices.size() <= _minimumTris)
	{
		triSet = _triSet;
		_count++;
		bounds = MakeAABBFromVerts(_triSet);
		return;
	}
	triSet = _triSet;
	_count++;
	bounds = MakeAABBFromVerts(_triSet);
	XMFLOAT3 center = AverageVert(triSet);
	float dx = bounds.max.x - bounds.min.x;
	float dy = bounds.max.y - bounds.min.y;
	float dz = bounds.max.z - bounds.min.z;
	XMFLOAT3 normal;
	float offset;
	if (dx > dy && dx > dz)
	{
		normal = XMFLOAT3(1, 0, 0);
		offset = center.x;
	}
	else if (dy > dz)
	{
		normal = XMFLOAT3(0, 1, 0);
		offset = center.y;
	}
	else
	{
		normal = XMFLOAT3(0, 0, 1);
		offset = center.z;
	}
	vector<unsigned int> t1;
	vector<unsigned int> t2;
	for (unsigned int i = 0; i < triSet.triIndices.size(); i++)
	{
		XMVECTOR pos = triSet.tris[triSet.triIndices[i]].centroid;
		int p2p = PointToPlane(normal, offset, XMFLOAT3(pos.m128_f32[0], pos.m128_f32[1], pos.m128_f32[2]));
		if (p2p == 1)
		{
			t1.push_back(triSet.triIndices[i]);
		}
		else
		{
			t2.push_back(triSet.triIndices[i]);
		}
	}

	TriangleSet s1 = triSet;
	s1.triIndices = t1;
	TriangleSet s2 = triSet;
	s2.triIndices = t2;

	left = new Node();
	left->parent = this;
	left->Analyze(s1, _count, _minimumTris);
	right = new Node();
	right->parent = this;
	right->Analyze(s2, _count, _minimumTris);
}

bool BoundingVolumeHeirarchy::Node::RayCast(XMFLOAT3& _outPos, float& _outDistance, XMFLOAT3 _rayStart, XMFLOAT3 _rayNormal)
{
	if (_rayStart.x > bounds.min.x && Dot(_rayNormal, XMFLOAT3(1, 0, 0)) < 0) return false;
	if (_rayStart.y > bounds.min.y && Dot(_rayNormal, XMFLOAT3(0, 1, 0)) < 0) return false;
	if (_rayStart.z > bounds.min.z && Dot(_rayNormal, XMFLOAT3(0, 0, 1)) < 0) return false;
	if (_rayStart.x > bounds.max.x && Dot(_rayNormal, XMFLOAT3(1, 0, 0)) > 0) return false;
	if (_rayStart.y > bounds.max.y && Dot(_rayNormal, XMFLOAT3(0, 1, 0)) > 0) return false;
	if (_rayStart.z > bounds.max.z && Dot(_rayNormal, XMFLOAT3(0, 0, 1)) > 0) return false;

	bool hasChildren = left != nullptr && right != nullptr;
	if (hasChildren)
	{
		XMFLOAT3 lPos;
		XMFLOAT3 rPos;
		float lDist;
		float rDist;
		bool l = left->RayCast(lPos, lDist, _rayStart, _rayNormal);
		bool r = right->RayCast(rPos, rDist, _rayStart, _rayNormal);
		if (!l && !r)
			return false;
		if (l && r)
		{
			if (lDist < rDist)
			{
				_outPos = lPos;
				_outDistance = lDist;
			}
			else
			{
				_outPos = rPos;
				_outDistance = rDist;
			}
			return true;
		}
		if (l)
		{
			_outPos = lPos;
			_outDistance = lDist;
			return true;
		}
		if (r)
		{
			_outPos = rPos;
			_outDistance = rDist;
			return true;
		}
	}
	Triangle t = triSet.tris[triSet.triIndices[0]];
	return RayToTriangle(_outPos, _outDistance, t.a.position, t.b.position, t.c.position, _rayStart, _rayNormal);
}

void BoundingVolumeHeirarchy::Node::Shutdown() const
{
	if (left)
	{
		left->Shutdown();
		delete left;
	}
	if (right)
	{
		right->Shutdown();
		delete right;
	}
}

XMFLOAT3 BoundingVolumeHeirarchy::AverageVert(TriangleSet _triSet)
{
	XMFLOAT3 ret(0, 0, 0);
	for (unsigned int i = 0; i < _triSet.triIndices.size(); i++)
	{
		ret.x += _triSet.tris[_triSet.triIndices[i]].centroid.m128_f32[0];
		ret.y += _triSet.tris[_triSet.triIndices[i]].centroid.m128_f32[1];
		ret.z += _triSet.tris[_triSet.triIndices[i]].centroid.m128_f32[2];
	}
	float invSize = 1.0f / _triSet.triIndices.size();
	ret.x *= invSize;
	ret.y *= invSize;
	ret.z *= invSize;
	return ret;
}

AABB BoundingVolumeHeirarchy::MakeAABBFromVerts(TriangleSet _triSet)
{
	AABB ret;
	ret.min = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	ret.max = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	auto min = [](float _a, float _b) -> float { return _a < _b ? _a : _b; };
	auto max = [](float _a, float _b) -> float { return _a > _b ? _a : _b; };
	for (unsigned int i = 0; i < _triSet.triIndices.size(); i++)
	{
		ret.min.x = min(ret.min.x, _triSet.tris[_triSet.triIndices[i]].centroid.m128_f32[0]);
		ret.min.y = min(ret.min.y, _triSet.tris[_triSet.triIndices[i]].centroid.m128_f32[1]);
		ret.min.z = min(ret.min.z, _triSet.tris[_triSet.triIndices[i]].centroid.m128_f32[2]);
		ret.max.x = max(ret.max.x, _triSet.tris[_triSet.triIndices[i]].centroid.m128_f32[0]);
		ret.max.y = max(ret.max.y, _triSet.tris[_triSet.triIndices[i]].centroid.m128_f32[1]);
		ret.max.z = max(ret.max.z, _triSet.tris[_triSet.triIndices[i]].centroid.m128_f32[2]);
	}
	return ret;
}

int BoundingVolumeHeirarchy::PointToPlane(XMFLOAT3 _normal, float _offset, XMFLOAT3 _point)
{
	float d = (_normal.x * _point.x + _normal.y * _point.y + _normal.z * _point.z) - _offset;
	return d < 0 ? 2 : 1;
}

float BoundingVolumeHeirarchy::Dot(XMFLOAT3 _a, XMFLOAT3 _b)
{
	return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z;
}

bool BoundingVolumeHeirarchy::RayToTriangle(XMFLOAT3& _outPos, float& _outDistance, XMFLOAT4 _a, XMFLOAT4 _b, XMFLOAT4 _c, XMFLOAT3 _rayStart, XMFLOAT3 _rayNormal)
{
	XMVECTOR a = XMVectorSet(_a.x, _a.y, _a.z, 1);
	XMVECTOR b = XMVectorSet(_b.x, _b.y, _b.z, 1);
	XMVECTOR c = XMVectorSet(_c.x, _c.y, _c.z, 1);
	XMVECTOR ab = XMVector3Normalize(b - a);
	XMVECTOR ac = XMVector3Normalize(c - a);
	XMVECTOR planeNormal = XMVector3Cross(ac, ab);
	//XMVECTOR toPoint = XMVectorSet(_rayStart.x, _rayStart.y, _rayStart.z, 1) - a;
	XMVECTOR rayNormal = XMVectorSet(_rayNormal.x, _rayNormal.y, _rayNormal.z, 1);
	XMVECTOR rayStart = XMVectorSet(_rayStart.x, _rayStart.y, _rayStart.z, 1);
	float d0 = XMVector3Dot(planeNormal, rayStart).m128_f32[0];
	float d1 = XMVector3Dot(planeNormal, a).m128_f32[0];
	float d2 = d0 - d1;
	float d3 = XMVector3Dot(planeNormal, rayNormal).m128_f32[0];
	float df = -(d2 / d3);
	/*df = abs(df);
	if (df > INT_MAX)
		return false;*/
	XMVECTOR cp = rayStart + rayNormal * df;
	XMVECTOR edge0 = b - a;
	XMVECTOR edge1 = c - b;
	XMVECTOR edge2 = a - c;
	XMVECTOR norm0 = XMVector3Normalize(XMVector3Cross(edge0, planeNormal));
	XMVECTOR norm1 = XMVector3Normalize(XMVector3Cross(edge1, planeNormal));
	XMVECTOR norm2 = XMVector3Normalize(XMVector3Cross(edge2, planeNormal));
	if (XMVector3Dot(norm0, cp - a).m128_f32[0] > 0) return false;
	if (XMVector3Dot(norm1, cp - b).m128_f32[0] > 0) return false;
	if (XMVector3Dot(norm2, cp - c).m128_f32[0] > 0) return false;

	_outDistance = df;
	_outPos = XMFLOAT3(cp.m128_f32[0], cp.m128_f32[1], cp.m128_f32[2]);
	return true;
}

TriangleSet BoundingVolumeHeirarchy::CreateTriangleSet(Mesh* _mesh)
{
	TriangleSet ret;
	ret.mesh = _mesh;
	vector<Vertex> verts = _mesh->GetVertexData();
	vector<unsigned int> tris = _mesh->GetTris();
	unsigned int triCount = tris.size() / 3;
	for (unsigned int i = 0; i < triCount; i++)
	{
		Triangle tri;
		tri.a = verts[tris[i * 3]];
		tri.b = verts[tris[i * 3 + 1]];
		tri.c = verts[tris[i * 3 + 2]];
		XMVECTOR a = XMVectorSet(tri.a.position.x, tri.a.position.y, tri.a.position.z, 1);
		XMVECTOR b = XMVectorSet(tri.b.position.x, tri.b.position.y, tri.b.position.z, 1);
		XMVECTOR c = XMVectorSet(tri.c.position.x, tri.c.position.y, tri.c.position.z, 1);
		tri.centroid = (a + b + c) / 3;
		ret.tris.push_back(tri);
	}
	for (unsigned int i = 0; i < ret.tris.size(); i++)
		ret.triIndices.push_back(i);
	return ret;
}

BoundingVolumeHeirarchy::BoundingVolumeHeirarchy() : count(0)
{
}

BoundingVolumeHeirarchy::~BoundingVolumeHeirarchy()
{
	if (root)
	{
		root->Shutdown();
		delete root;
	}
}

void BoundingVolumeHeirarchy::Analyze(Mesh* _mesh, unsigned int _minimumTris)
{
	assert(_mesh);
	assert(_minimumTris);
	root = new Node();
	root->Analyze(CreateTriangleSet(_mesh), count, _minimumTris);
}

bool BoundingVolumeHeirarchy::RayCast(XMFLOAT3& _outPos, XMFLOAT3 _rayStart, XMFLOAT3 _rayNormal) const
{
	float distance;
	return root->RayCast(_outPos, distance, _rayStart, _rayNormal);
}