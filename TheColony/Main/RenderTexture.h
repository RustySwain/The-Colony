#pragma once
#include <DirectXMath.h>
#include "d3d11.h"
#include <DirectXMath.h>
#include "Macros.h"

using namespace DirectX;

class RenderTexture
{
public:
	RenderTexture();
	~RenderTexture();

	void Initialize(ID3D11Device *device, int textureWidth, int textureHeight, float screenFar, float screenNear);
	void Shutdown();
	void SetRenderTarget(ID3D11DeviceContext *deviceContext);
	void ClearRenderTarget(ID3D11DeviceContext* deviceContext, float red, float green, float blue, float alpha);
	void ClearScreen(ID3D11DeviceContext* deviceContext);
	ID3D11ShaderResourceView* GetShaderResourceView() const;
	void GetProjectionMatrix(XMMATRIX &projectionMatrix);
	void GetOrthoMatrix(XMMATRIX &orthoMatrix);

private:
	ID3D11Texture2D *_renderTargetTexture = nullptr;
	ID3D11RenderTargetView *_renderTargetView = nullptr;
	ID3D11ShaderResourceView *_shaderResourceView = nullptr;
	ID3D11Texture2D *_depthStencilBuffer = nullptr;
	ID3D11DepthStencilView *_depthStencilView = nullptr;
	D3D11_VIEWPORT _viewport;
	XMMATRIX _projectionMatrix;
	XMMATRIX _orthoMatrix;
};

