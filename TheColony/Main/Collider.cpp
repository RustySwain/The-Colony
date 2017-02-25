#include "Collider.h"
#include "Transform.h"

Collider::Collider()
{
}

Collider::~Collider()
{
}

void Collider::Start()
{
}

void Collider::Update()
{
}

void Collider::OnDelete()
{
}

void Collider::LoadFromFile(fstream& _file)
{
}

void Collider::SetMesh(Mesh* _mesh)
{
	bvh.Analyze(_mesh, 1, gameObject->GetComponent<Transform>()->GetWorldMatrix());
}

bool Collider::RayCast(XMFLOAT3& _outPos, XMFLOAT3 _rayStart, XMFLOAT3 _rayNormal) const
{
	return bvh.RayCast(_outPos, _rayStart, _rayNormal);
}