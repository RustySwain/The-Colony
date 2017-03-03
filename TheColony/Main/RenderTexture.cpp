#include "RenderTexture.h"
#include "Application.h"

RenderTexture::RenderTexture()
{
	_renderTargetTexture = nullptr;
	_renderTargetView = nullptr;
	_shaderResourceView = nullptr;
	_depthStencilBuffer = nullptr;
	_depthStencilView = nullptr;
}


RenderTexture::~RenderTexture()
{
}

void RenderTexture::Initialize(ID3D11Device *device, int textureWidth, int textureHeight, float screenFar, float screenNear)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	//D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	//D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

	// Initialize the render target texture description.
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	// Setup the render target texture description.
	textureDesc.Width = textureWidth;//(float)DXApp::GetInstance()->windowRect.right;
	textureDesc.Height = textureHeight;//(float)DXApp::GetInstance()->windowRect.bottom;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	device->CreateTexture2D(&textureDesc, nullptr, &_renderTargetTexture);

	// Setup the description of the shader resource view.
	shaderResourceViewDesc.Format = DXGI_FORMAT_R32_FLOAT;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	device->CreateShaderResourceView(_renderTargetTexture, &shaderResourceViewDesc, &_shaderResourceView);

	// Initailze the depth stencil view description.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));


	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	device->CreateDepthStencilView(_renderTargetTexture, &depthStencilViewDesc, &_depthStencilView);

	// Setup the viewport for rendering.
	_viewport.Width = (float)textureWidth;
	_viewport.Height = (float)textureHeight;
	_viewport.MinDepth = 0.0f;
	_viewport.MaxDepth = 1.0f;
	_viewport.TopLeftX = 0.0f;
	_viewport.TopLeftY = 0.0f;

	float fov = 70.0f;
	float nearPlane = 0.01f;
	float farPlane = 100.0f;
	// Setup the projection matrix.
	_projectionMatrix = XMMatrixPerspectiveFovRH(((float)XM_PI / 4.0f), /*((float)textureWidth / (float)textureHeight)*/ 1.0f, screenNear, screenFar);
	
	// Create an orthographic projection matrix for 2D rendering.
	_orthoMatrix = XMMatrixOrthographicRH((float)textureWidth, (float)textureHeight, screenNear, screenFar);
}

void RenderTexture::Shutdown()
{
	SAFE_RELEASE(_depthStencilView);
	SAFE_RELEASE(_depthStencilBuffer);
	SAFE_RELEASE(_shaderResourceView);
	SAFE_RELEASE(_renderTargetView);
	SAFE_RELEASE(_renderTargetTexture);
}

void RenderTexture::SetRenderTarget(ID3D11DeviceContext * deviceContext)
{
	// Bind the render target view and depth stencil buffer to the output render pipeline.
	deviceContext->OMSetRenderTargets(0, nullptr, _depthStencilView);

	// Set the viewport.
	deviceContext->RSSetViewports(1, &_viewport);
}

void RenderTexture::ClearRenderTarget(ID3D11DeviceContext * deviceContext, float red, float green, float blue, float alpha)
{
	float color[4];

	// Setup the color to clear the buffer to.
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	// Clear the back buffer.
	//deviceContext->ClearRenderTargetView(_renderTargetView, color);

	// Clear the depth buffer.
	deviceContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH| D3D11_CLEAR_STENCIL, 1.0f, 0);
	
}

void RenderTexture::ClearScreen(ID3D11DeviceContext * deviceContext)
{
	ID3D11ShaderResourceView* pNullSRV = nullptr;
	deviceContext->PSSetShaderResources(4, 1, &pNullSRV);

	ID3D11RenderTargetView* nullRTV = nullptr;
	deviceContext->OMSetRenderTargets(1, &nullRTV, nullptr);
}

ID3D11ShaderResourceView* RenderTexture::GetShaderResourceView() const
{
	return _shaderResourceView;
}

void RenderTexture::GetProjectionMatrix(XMMATRIX & projectionMatrix)
{
	projectionMatrix = _projectionMatrix;
}

void RenderTexture::GetOrthoMatrix(XMMATRIX & orthoMatrix)
{
	orthoMatrix = _orthoMatrix;
}
