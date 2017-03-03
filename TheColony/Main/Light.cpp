#include "Light.h"
#include "Application.h"
#include <fstream>
#include "Time.h"

Light::Light() : type(NONE)
{
}

Light::~Light()
{
}

void Light::Start()
{
	Application::GetInstance()->RegisterLight(this);

	/*GenerateViewMatrix();
	GenerateProjectionMatrix(100, 0.01f);*/

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

	//TEST
	if (type == DIRECTIONAL)
	{
		GenerateProjectionMatrix(100, 0.01f);
		GenerateViewMatrix();
	}
	//END TEST
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

void Light::SetLookAt(float x, float y, float z)
{
	_lookAt.x = x;
	_lookAt.y = y;
	_lookAt.z = z;
	_lookAt.w = 1;
}

void Light::GenerateViewMatrix() 
{
	XMFLOAT4 up;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	up.w = 1.0f;

	XMVECTOR pos, look, _up;
	XMFLOAT3 transform = gameObject->GetComponent<Transform>()->GetWorldPosition();
	pos = XMVectorSet(transform.x, transform.y, transform.z, 1.0f);
	look = XMVectorSet(_lookAt.x, _lookAt.y, _lookAt.z, 1.0f);
	_up = XMVectorSet(up.x, up.y, up.z, 0.0f);

	_viewMatrix = XMMatrixLookAtRH(pos, look, _up);
	lightMatrices.lightView = _viewMatrix;
}

void Light::GenerateProjectionMatrix(float screenFar, float screenNear) 
{
	float fieldOfView, screenAspect;

	// Setup field of view and screen aspect for a square light source.
	fieldOfView = ((float)XM_PI / 2.0f);
	screenAspect = 1.0f;

	// Create the projection matrix for the light.
	//_projectionMatrix = XMMatrixPerspectiveFovRH(fieldOfView, screenAspect, screenNear, screenFar);
	_projectionMatrix = XMMatrixOrthographicRH(100, 100, 1.0f, 50.0f);
	//_projectionMatrix = XMMatrixOrthographicOffCenterRH(0, 100, 100, 0, 1.0f, 50.0f);
	lightMatrices.lightProj = _projectionMatrix;
}

Light::LightBufferType Light::GetLightBuffType() const
{
	return lightBuffType;
}

Light::LightMatrices Light::GetLightMatrices() const
{
	return lightMatrices;
}
