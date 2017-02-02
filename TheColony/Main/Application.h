#pragma once
#include "d3d11.h"

#pragma comment(lib, "d3d11.lib")

class Application
{
	static Application* instance;

	// Windows
	HWND* window = nullptr;
	RECT windowRect;

	// DirectX
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* screenTargetView = nullptr;
	ID3D11Texture2D* backBuffer = nullptr;
	ID3D11InputLayout* layout = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;
	ID3D11BlendState* blendState = nullptr;
	ID3D11RasterizerState* rasterState = nullptr;

	ID3D11VertexShader* vsMesh = nullptr;

	float backBufferColor[4] = { 0, 1, 1, 1 };

	void CreateDevice();
	void CreateRenderTarget();
	void CreateLayout();
	void CreateShaders();
	void CreateDepthStencil();
	void CreateBlendState();
	void CreateRasterState();

public:
	Application();
	~Application();

	static Application* GetInstance() { if (!instance) instance = new Application(); return instance; };

	RECT& GetWindowRect() { return windowRect; };

	void Init(HWND& _window);
	void Update();
	void Render();
	void Shutdown();
};