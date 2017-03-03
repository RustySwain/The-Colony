#include "Depth.h"
#include "DepthPixelShader.csh"
#include "DepthVertexShader.csh"

Depth::Depth()
{
	_vertexShader = nullptr;
	_pixelShader = nullptr;
	_layout = nullptr;
	_matrixBuffer = nullptr;
}


Depth::~Depth()
{
}

void Depth::Initialize(ID3D11Device *_dev)
{
	InitializeShader(_dev);
}

void Depth::Shutdown()
{
	ShutdownShader();
}

void Depth::Render(ID3D11DeviceContext * _devCon, const UINT indexCount, XMMATRIX &worldMatrix, XMMATRIX &viewMatrix, XMMATRIX &projectionMatrix)
{
	SetShaderParams(_devCon, worldMatrix, viewMatrix, projectionMatrix);

	RenderShader(_devCon, indexCount);
}

void Depth::InitializeShader(ID3D11Device * _dev)
{
	D3D11_BUFFER_DESC matrixBufferDesc;

	_dev->CreateVertexShader(DepthVertexShader, sizeof(DepthVertexShader), 0, &_vertexShader);
	_dev->CreatePixelShader(DepthPixelShader, sizeof(DepthPixelShader), 0, &_pixelShader);

	D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	_dev->CreateInputLayout(layoutDesc, ARRAYSIZE(layoutDesc), DepthVertexShader, sizeof(DepthVertexShader), &_layout);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = 0;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	_dev->CreateBuffer(&matrixBufferDesc, nullptr, &_matrixBuffer);
}

void Depth::ShutdownShader()
{
	SAFE_RELEASE(_matrixBuffer);
	SAFE_RELEASE(_layout);
	SAFE_RELEASE(_pixelShader);
	SAFE_RELEASE(_vertexShader);
}

void Depth::SetShaderParams(ID3D11DeviceContext *_devCon, XMMATRIX &worldMatrix, XMMATRIX &viewMatrix, XMMATRIX &projectionMatrix)
{
	//D3D11_MAPPED_SUBRESOURCE mappedResource;
	unsigned int bufferNumber;
	MatrixBufferType dataPtr;

	// Copy the matrices into the constant buffer.
	dataPtr.world = worldMatrix;
	dataPtr.view = viewMatrix;
	dataPtr.projection = projectionMatrix;

	_devCon->UpdateSubresource(_matrixBuffer, 0, 0, &dataPtr, 0, 0);

	bufferNumber = 0;

	_devCon->VSSetConstantBuffers(bufferNumber, 1, &_matrixBuffer);
}

void Depth::RenderShader(ID3D11DeviceContext * _devCon, int indexCount)
{
	// Set the vertex input layout.
	_devCon->IASetInputLayout(_layout);

	_devCon->VSSetShader(_vertexShader, nullptr, 0);
	_devCon->PSSetShader(_pixelShader, nullptr, 0);

	_devCon->DrawIndexed(indexCount, 0, 0);
}

