#include "Camera.h"
#include "Application.h"
#include "Macros.h"

Camera* Camera::mainCam = nullptr;

void Camera::UpdateProjMat()
{
	RECT winRect = Application::GetInstance()->GetWindowRect();
	projectionMatrix = XMMatrixPerspectiveFovRH(fov, (float)winRect.right / winRect.bottom, nearPlane, farPlane);
}

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Start()
{
	// set this to be the main camera if none exists
	if (mainCam == nullptr)
		mainCam = this;
	// create viewport to be the full window size
	RECT winRect = Application::GetInstance()->GetWindowRect();
	viewport.Height = (float)winRect.bottom;
	viewport.Width = (float)winRect.right;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	// create view and projection matrices and the constant buffer
	D3D11_BUFFER_DESC bDesc;
	ZeroMemory(&bDesc, sizeof(bDesc));
	bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bDesc.ByteWidth = sizeof(XMMATRIX) * 2;

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(subData));

	UpdateProjMat();

	XMMATRIX mats[2] = { viewMatrix, projectionMatrix };

	subData.pSysMem = mats;

	Application::GetInstance()->GetDevice()->CreateBuffer(&bDesc, &subData, &constantBuffer);
}

void Camera::Update()
{
	// update view matrix and projection matrix and then update constant buffer
	XMFLOAT4X4 viewFloat;
	XMStoreFloat4x4(&viewFloat, viewMatrix);
	viewMatrix = XMMatrixInverse(0, gameObject->GetComponent<Transform>()->GetWorldMatrix());
	ID3D11DeviceContext* context = Application::GetInstance()->GetContext();
	XMMATRIX mats[2] = { viewMatrix, projectionMatrix };
	context->UpdateSubresource(constantBuffer, 0, 0, mats, 0, 0);
}

void Camera::OnDelete()
{
	SAFE_RELEASE(constantBuffer);
}

void Camera::LoadFromString(string _str)
{
}

string Camera::WriteToString() const
{
	return string();
}