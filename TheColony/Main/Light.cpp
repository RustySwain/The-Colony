#include "Light.h"
#include "Application.h"

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