#pragma once
#include "GameObject.h"
#include "DirectXMath.h"

using namespace DirectX;

// Dependencies: None
class Transform : public Component
{
	const unsigned int id = 1;

	Transform* parent = nullptr;
	XMMATRIX localMatrix;
	float scale = 1;

public:
	Transform();
	~Transform();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual void LoadFromFile(fstream &_file) override;

	void RotateXPre(float _angle);
	void RotateYPre(float _angle);
	void RotateZPre(float _angle);

	void RotateXPost(float _angle);
	void RotateYPost(float _angle);
	void RotateZPost(float _angle);

	void ScalePre(float _scale);
	void ScalePost(float _scale);
	float GetScale() const;

	void TranslatePre(XMFLOAT3 _translation);
	void TranslatePost(XMFLOAT3 _translation);

	// Fast
	XMMATRIX GetLocalMatrix() const;
	// Slow. If you aren't updating this, just store it instead of calling this every frame.
	XMMATRIX GetWorldMatrix() const;

	void SetLocalPosition(float _x, float _y, float _z);
	void SetLocalMatrix(XMMATRIX _matrix);
	XMFLOAT3 GetWorldPosition() const;

	void SetParent(Transform* _parent);
	Transform* GetParent();
};
