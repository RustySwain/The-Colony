#pragma once
#include "d3d11.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Light.h"

#pragma comment(lib, "d3d11.lib")

class Application
{
	static Application* instance;

public:
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
	ID3D11Buffer* camPosBuffer = nullptr;
	ID3D11Buffer* lightBuffer = nullptr;

	ID3D11VertexShader* vsMesh = nullptr;
	ID3D11PixelShader* psMesh = nullptr;
	ID3D11PixelShader* psSkybox = nullptr;

	float backBufferColor[4] = { 0, 1, 1, 1 };
	unsigned int msCount = 8;
	unsigned int msQuality = D3D11_STANDARD_MULTISAMPLE_PATTERN;

	GameObject gameObjectManager;
	vector<const MeshRenderer*> renderers;
	vector<const Camera*> cameras;
	vector<const Light*> lights;

	void CreateDevice();
	void CreateRenderTarget();
	void CreateLayout();
	void CreateShaders();
	void CreateDepthStencil();
	void CreateBlendState();
	void CreateRasterState();
	void CreateCameraAndLightBuffer();
	void CreateBuffer(D3D11_BUFFER_DESC* _bData, D3D11_SUBRESOURCE_DATA* _subData, ID3D11Buffer** _buffer) const;


public:
	Application();
	~Application();

	static Application* GetInstance() { if (!instance) instance = new Application(); return instance; };

	RECT& GetWindowRect() { return windowRect; };
	ID3D11Device* GetDevice() const { return device; };
	ID3D11DeviceContext* GetContext() const { return context; };

	ID3D11PixelShader* GetPSMesh() const { return psMesh; };
	ID3D11PixelShader* GetPSSkybox() const { return psSkybox; };
	ID3D11VertexShader* GetVSMesh() const { return vsMesh; };

	void RegisterMeshRenderer(const MeshRenderer* _mr);
	void UnRegisterMeshRenderer(const MeshRenderer* _mr);

	void RegisterCamera(const Camera* _cam);
	void UnregisterCamera(const Camera* _cam);

	void RegisterLight(const Light* _light);
	void UnregisterLight(const Light* _light);

	void Init(HWND& _window);
	void Update() const;
	void Render() const;
	void Shutdown();
};