#include "Collider.h"
#include "Transform.h"

vector<const Collider*> Collider::registeredColliders;

Collider::Collider()
{
}

Collider::~Collider()
{
}

void Collider::Start()
{
	registeredColliders.push_back(this);
}

void Collider::Update()
{
}

void Collider::OnDelete()
{
	registeredColliders.erase(find(registeredColliders.begin(), registeredColliders.end(), this));
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
	float distance;
	return bvh.RayCast(_outPos, distance, _rayStart, _rayNormal);
}

bool Collider::RayCastAll(XMFLOAT3& _outPos, XMFLOAT3 _rayStart, XMFLOAT3 _rayNormal)
{
	float distance = FLT_MAX;
	XMFLOAT3 retHit;
	for (size_t i = 0; i < registeredColliders.size(); i++)
	{
		float d;
		XMFLOAT3 hit;
		bool cast = registeredColliders[i]->bvh.RayCast(hit, d, _rayStart, _rayNormal);
		if (cast)
		{
			if (d < distance)
			{
				retHit = hit;
				distance = d;
			}
		}
	}
	if (distance == FLT_MAX)
		return false;
	_outPos = retHit;
	return true;
}