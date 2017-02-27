#pragma once
#include "GameObject.h"
#include "BoundingVolumeHeirarchy.h"

class Collider : public Component
{
	const unsigned int id = 3;
	BoundingVolumeHeirarchy bvh;

	static vector<const Collider*> registeredColliders;

public:
	Collider();
	~Collider();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	void SetMesh(Mesh* _mesh);
	bool RayCast(XMFLOAT3& _outPos, XMFLOAT3 _rayStart, XMFLOAT3 _rayNormal) const;
	static bool RayCastAll(XMFLOAT3& _outPos, GameObject*& _castedObject, XMFLOAT3 _rayStart, XMFLOAT3 _rayNormal);
};
