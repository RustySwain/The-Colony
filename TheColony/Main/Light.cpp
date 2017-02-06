#include "Light.h"
#include "Application.h"
#include <fstream>

Light::Light() : type(LightType::NONE)
{
}

Light::~Light()
{
}

void Light::Start()
{
	Application::GetInstance()->RegisterLight(this);
}

void Light::Update()
{
	// update buffer struct to have transform stuff
	Transform* transform = gameObject->GetComponent<Transform>();
	XMFLOAT4X4 worldMat;
	XMStoreFloat4x4(&worldMat, gameObject->GetComponent<Transform>()->GetWorldMatrix());
	lightBuffType.lightDirection = XMFLOAT4(worldMat.m[2][0], worldMat.m[2][1], worldMat.m[2][2], 1);
	XMFLOAT3 wPos = transform->GetWorldPosition();
	lightBuffType.lightPos = XMFLOAT4(wPos.x, wPos.y, wPos.z, 1);
	lightBuffType.lightPos.w = (float)type;
}

void Light::OnDelete()
{
	Application::GetInstance()->UnregisterLight(this);
}

void Light::LoadFromFile(fstream & _file)
{
	XMFLOAT4 color;
	_file.read((char*)&color.x, sizeof(float));
	_file.read((char*)&color.y, sizeof(float));
	_file.read((char*)&color.z, sizeof(float));
	_file.read((char*)&color.w, sizeof(float));
	SetColor(color);

	XMFLOAT4 extra;
	_file.read((char*)&extra.x, sizeof(float));
	_file.read((char*)&extra.y, sizeof(float));
	_file.read((char*)&extra.z, sizeof(float));
	_file.read((char*)&extra.w, sizeof(float));
	SetExtra(extra);

	int lightType;
	_file.read((char*)&lightType, sizeof(int));
	LightType lType;
	switch (lightType)
	{
	case AMBIENT:
		lType = AMBIENT;
		break;
	case DIRECTIONAL:
		lType = DIRECTIONAL;
		break;
	case POINT:
		lType = POINT;
		break;
	case SPOT:
		lType = SPOT;
		break;
	default:
		lType = NONE;
		break;
	}
	type = lType;
}

void Light::LoadFromString(string _str)
{
}

string Light::WriteToString() const
{
	return string();
}

void Light::SetColor(XMFLOAT4 _color)
{
	lightBuffType.diffuseColor = _color;
}

void Light::SetExtra(XMFLOAT4 _extra)
{
	lightBuffType.extra = _extra;
}

Light::LightBufferType Light::GetLightBuffType() const
{
	return lightBuffType;
}