#include "Application.h"
#include "Macros.h"
#include "Defines.h"

// Sahders
#include "VSMesh.csh"
#include <cmath>

Application* Application::instance = nullptr;

void Application::CreateDevice()
{
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZMem(swapDesc);
	swapDesc.BufferCount = DXGI_MAX_SWAP_CHAIN_BUFFERS;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.Width = windowRect.right;
	swapDesc.BufferDesc.Height = windowRect.bottom;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = *window;
	swapDesc.SampleDesc.Count = MS_COUNT;
	swapDesc.SampleDesc.Quality = MS_QUALITY;
	swapDesc.Windowed = true;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;

	unsigned int flags = 0;
#if _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, flags, 0, 0, D3D11_SDK_VERSION, &swapDesc, &swapChain, &device, 0, &context);
}

void Application::CreateRenderTarget()
{
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	device->CreateRenderTargetView(backBuffer, 0, &screenTargetView);
}

void Application::CreateLayout()
{
	D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "JOINT_INDEX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "JOINT_WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "FLAGS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	device->CreateInputLayout(layoutDesc, ARRAYSIZE(layoutDesc), VSMesh, sizeof(VSMesh), &layout);
}

void Application::CreateShaders()
{
	device->CreateVertexShader(VSMesh, sizeof(VSMesh), 0, &vsMesh);
}

void Application::CreateDepthStencil()
{
	CD3D11_TEXTURE2D_DESC depthStencilDesc(DXGI_FORMAT_D24_UNORM_S8_UINT, lround(windowRect.right), lround(windowRect.bottom), 1, 1, D3D11_BIND_DEPTH_STENCIL, D3D11_USAGE_DEFAULT, 0, MS_COUNT, MS_QUALITY);

	ID3D11Texture2D* depthStencil;
	device->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencil);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZMem(depthStencilViewDesc);
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	device->CreateDepthStencilView(depthStencil, &depthStencilViewDesc, &depthStencilView);
	SAFE_RELEASE(depthStencil);
}

void Application::CreateBlendState()
{
	D3D11_BLEND_DESC blendDesc;
	ZMem(blendDesc);
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	device->CreateBlendState(&blendDesc, &blendState);
}

void Application::CreateRasterState()
{
	D3D11_RASTERIZER_DESC raDesc;
	ZMem(raDesc);
	raDesc.AntialiasedLineEnable = true;
	raDesc.MultisampleEnable = true;
	raDesc.FillMode = D3D11_FILL_SOLID;
	raDesc.CullMode = D3D11_CULL_BACK;
	device->CreateRasterizerState(&raDesc, &rasterState);
	context->RSSetState(rasterState);
}

Application::Application()
{
}

Application::~Application()
{
}

void Application::Init(HWND& _window)
{
	window = &_window;
	CreateDevice();
	CreateRenderTarget();
	CreateLayout();
	CreateShaders();
	CreateDepthStencil();
	CreateBlendState();
	CreateRasterState();
	gameObjectManager.Start();
}

void Application::Update() const
{
	gameObjectManager.Update();
}

void Application::Render() const
{
	context->OMSetRenderTargets(1, &screenTargetView, depthStencilView);
	context->ClearRenderTargetView(screenTargetView, backBufferColor);
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	float blendFactor[] = { 1, 1, 1, 1 };
	context->OMSetBlendState(blendState, blendFactor, 0xffffffff);
	swapChain->Present(0, 0);
}

void Application::Shutdown()
{
	SAFE_RELEASE(device);
	SAFE_RELEASE(context);
	SAFE_RELEASE(swapChain);
	SAFE_RELEASE(screenTargetView);
	SAFE_RELEASE(backBuffer);
	SAFE_RELEASE(layout);
	SAFE_RELEASE(depthStencilView);
	SAFE_RELEASE(blendState);
	SAFE_RELEASE(rasterState);

	// Shaders
	SAFE_RELEASE(vsMesh);

	gameObjectManager.OnDelete();
}