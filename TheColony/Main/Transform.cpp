#include "Transform.h"
#include "Defines.h"
#include <fstream>

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Start()
{
	localMatrix = XMMatrixIdentity();
}

void Transform::Update()
{
}

void Transform::OnDelete()
{
	
}

void Transform::LoadFromFile(fstream &_file)
{
	localMatrix = XMMatrixIdentity();

	float xPos, yPos, zPos;
	_file.read((char*)&xPos, sizeof(float));
	_file.read((char*)&yPos, sizeof(float));
	_file.read((char*)&zPos, sizeof(float));
	SetLocalPosition(xPos, yPos, zPos);

	float xRot, yRot, zRot;
	_file.read((char*)&xRot, sizeof(float));
	_file.read((char*)&yRot, sizeof(float));
	_file.read((char*)&zRot, sizeof(float));
	RotateXPre(xRot);
	RotateYPre(yRot);
	RotateZPre(zRot);

	float scale;
	_file.read((char*)&scale, sizeof(float));
	ScalePre(scale);
}

void Transform::LoadFromString(string _str)
{
}

string Transform::WriteToString() const
{
	string ret = "";
	ret += (char*)&localMatrix;
	unsigned int id = gameObject->GetId();
	ret += (char*)&id;
	ret += (char*)&scale;
	return ret;
}

void Transform::RotateXPre(float _angle)
{
	_angle *= (float)DEG2RAD;
	localMatrix = XMMatrixRotationX(_angle) * localMatrix;
}

void Transform::RotateYPre(float _angle)
{
	_angle *= (float)DEG2RAD;
	localMatrix = XMMatrixRotationY(_angle) * localMatrix;
}

void Transform::RotateZPre(float _angle)
{
	_angle *= (float)DEG2RAD;
	localMatrix = XMMatrixRotationZ(_angle) * localMatrix;
}

void Transform::RotateXPost(float _angle)
{
	_angle *= (float)DEG2RAD;
	localMatrix = localMatrix * XMMatrixRotationX(_angle);
}

void Transform::RotateYPost(float _angle)
{
	_angle *= (float)DEG2RAD;
	localMatrix = localMatrix * XMMatrixRotationY(_angle);
}

void Transform::RotateZPost(float _angle)
{
	_angle *= (float)DEG2RAD;
	localMatrix = localMatrix * XMMatrixRotationZ(_angle);
}

void Transform::ScalePre(float _scale)
{
	localMatrix = XMMatrixScaling(_scale, _scale, _scale) * localMatrix;
	scale = _scale;
}

void Transform::ScalePost(float _scale)
{
	localMatrix = localMatrix * XMMatrixScaling(_scale, _scale, _scale);
	scale = _scale;
}

float Transform::GetScale() const
{
	return scale;
}

void Transform::TranslatePre(XMFLOAT3 _translation)
{
	localMatrix = XMMatrixTranslation(_translation.x, _translation.y, _translation.z) * localMatrix;
}

void Transform::TranslatePost(XMFLOAT3 _translation)
{
	localMatrix = localMatrix * XMMatrixTranslation(_translation.x, _translation.y, _translation.z);
}

XMMATRIX Transform::GetLocalMatrix() const
{
	return localMatrix;
}

XMMATRIX Transform::GetWorldMatrix() const
{
	if (parent)
		return localMatrix * parent->GetWorldMatrix();
	return localMatrix;
}

void Transform::SetLocalPosition(float _x, float _y, float _z)
{
	XMFLOAT4X4 f;
	XMStoreFloat4x4(&f, localMatrix);
	f.m[3][0] = _x;
	f.m[3][1] = _y;
	f.m[3][2] = _z;
	localMatrix = XMLoadFloat4x4(&f);
}

void Transform::SetLocalMatrix(XMMATRIX _matrix)
{
	localMatrix = _matrix;
}

XMFLOAT3 Transform::GetWorldPosition() const
{
	XMMATRIX world = GetWorldMatrix();
	XMFLOAT4X4 f;
	XMStoreFloat4x4(&f, world);
	return XMFLOAT3(f.m[3][0], f.m[3][1], f.m[3][2]);
}

void Transform::SetParent(Transform* _parent)
{
	parent = _parent;
}

Transform * Transform::GetParent()
{
	return parent;
}
