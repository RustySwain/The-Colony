#pragma once
#include "GameObject.h"
#include "BoundingVolumeHeirarchy.h"

class Collider : public Component
{
	const unsigned int id = 3;
	BoundingVolumeHeirarchy bvh;

public:
	Collider();
	~Collider();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromFile(fstream &_file) override;

	void SetMesh(Mesh* _mesh);
	bool RayCast(XMFLOAT3& _outPos, XMFLOAT3 _rayStart, XMFLOAT3 _rayNormal) const;
};
