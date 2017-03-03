#pragma once
#include <DirectXMath.h>
#include "d3d11.h"
#include <DirectXMath.h>
#include "Macros.h"
using namespace DirectX;

class Depth
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

public:
	Depth();
	~Depth();

	void Initialize(ID3D11Device *_dev);
	void Shutdown();
	void Render(ID3D11DeviceContext *_devCon, const UINT indexCount, XMMATRIX &worldMatrix, XMMATRIX &viewMatrix, XMMATRIX &projectionMatrix);


private:
	void InitializeShader(ID3D11Device *_dev);
	void ShutdownShader();
	void SetShaderParams(ID3D11DeviceContext *_devCon, XMMATRIX &worldMatrix, XMMATRIX &viewMatrix, XMMATRIX &projectionMatrix);
	void RenderShader(ID3D11DeviceContext *_devCon, int indexCount);

private:
	ID3D11VertexShader *_vertexShader;
	ID3D11PixelShader *_pixelShader;
	ID3D11InputLayout *_layout;
	ID3D11Buffer *_matrixBuffer;
};

