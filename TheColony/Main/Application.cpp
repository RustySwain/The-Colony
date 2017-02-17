#include "Application.h"
#include "Macros.h"
#include "Defines.h"
#include <cmath>
#include "GameObjectManager.h"

// Shaders
#include "VSMesh.csh"
#include "VSUI.csh"
#include "PSMesh.csh"
#include "PSSkybox.csh"
#include "PSUI.csh"

Application* Application::instance = nullptr;

void Application::SortMeshesByDistance()
{
	// this will replace the meshrenderer vector
	vector<const MeshRenderer*> newMeshes;
	vector<const MeshRenderer*> uiMeshes;
	for (size_t i = 0; i < renderers.size(); i++)
	{
		// find the skybox
		if (renderers[i]->GetType() == MeshRenderer::SKYBOX)
		{
			// put it in the new vector and remove from the old one
			newMeshes.push_back(renderers[i]);
			renderers.erase(renderers.begin() + i);
			break;
		}
	}
	for (size_t i = 0; i < renderers.size(); i++)
	{
		// push back all of the opaque objects first. It should be front to back to prevent pixel redraws, but this is plenty efficient for now
		if (!renderers[i]->GetTransparent())
		{
			if (renderers[i]->GetType() == MeshRenderer::UI)
			{
				uiMeshes.push_back(renderers[i]);
				renderers.erase(renderers.begin() + i--);
				continue;
			}
			// put it in the new vector and remove from the old one
			newMeshes.push_back(renderers[i]);
			renderers.erase(renderers.begin() + i--);
		}
	}
	// while there are still items in the vector
	while (renderers.size())
	{
		unsigned int farthest = 0;
		float distance = -FLT_MAX;
		for (unsigned int i = 0; i < renderers.size(); i++)
		{
			if (renderers[i]->GetType() == MeshRenderer::UI)
			{
				uiMeshes.push_back(renderers[i]);
				renderers.erase(renderers.begin() + i--);
				continue;
			}
			// get distance between main camera and mesh transform
			XMFLOAT3 camPos = Camera::mainCam->gameObject->GetComponent<Transform>()->GetWorldPosition();
			XMFLOAT3 meshPos = renderers[i]->gameObject->GetComponent<Transform>()->GetWorldPosition();
			XMVECTOR camVecPos = XMVectorSet(camPos.x, camPos.y, camPos.z, 1);
			XMVECTOR meshVecPos = XMVectorSet(meshPos.x, meshPos.y, meshPos.z, 1);
			float thisDist = XMVector3Length(meshVecPos - camVecPos).m128_f32[0];
			// if this is farther away than the temporary farthest, this becomes the temporary farthest
			if (thisDist > distance)
			{
				distance = thisDist;
				farthest = i;
			}
		}
		// put the farthest into the new vector and remove it from the old one
		newMeshes.push_back(renderers[farthest]);
		renderers.erase(renderers.begin() + farthest);
	}
	while (uiMeshes.size())
	{
		unsigned int farthest = 0;
		float distance = -FLT_MAX;
		for (unsigned int i = 0; i < uiMeshes.size(); i++)
		{
			// get distance between main camera and mesh transform
			float thisDist = uiMeshes[i]->gameObject->GetComponent<Transform>()->GetWorldPosition().z;
			// if this is farther away than the temporary farthest, this becomes the temporary farthest
			if (thisDist > distance)
			{
				distance = thisDist;
				farthest = i;
			}
		}
		// put the farthest into the new vector and remove it from the old one
		newMeshes.push_back(uiMeshes[farthest]);
		uiMeshes.erase(uiMeshes.begin() + farthest);
	}
	// replace the vector
	renderers = newMeshes;
}

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
	swapDesc.SampleDesc.Count = msCount;
	swapDesc.SampleDesc.Quality = msQuality;
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
	D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "JOINT_INDEX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "JOINT_WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "FLAGS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "INSTANCE", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "INSTANCE", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "INSTANCE", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "INSTANCE", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	};
	device->CreateInputLayout(layoutDesc, ARRAYSIZE(layoutDesc), VSMesh, sizeof(VSMesh), &layout);
}

void Application::CreateShaders()
{
	device->CreateVertexShader(VSMesh, sizeof(VSMesh), 0, &vsMesh);
	device->CreateVertexShader(VSUI, sizeof(VSUI), 0, &vsUI);
	device->CreatePixelShader(PSMesh, sizeof(PSMesh), 0, &psMesh);
	device->CreatePixelShader(PSSkybox, sizeof(PSSkybox), 0, &psSkybox);
	device->CreatePixelShader(PSUI, sizeof(PSUI), 0, &psUI);
}

void Application::CreateDepthStencil()
{
	CD3D11_TEXTURE2D_DESC depthStencilDesc(DXGI_FORMAT_D24_UNORM_S8_UINT, lround(windowRect.right), lround(windowRect.bottom), 1, 1, D3D11_BIND_DEPTH_STENCIL, D3D11_USAGE_DEFAULT, 0, msCount, msQuality);

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
void Application::CreateCameraAndLightBuffer()
{
	// initialize the lightbuffer and camera position buffer
	D3D11_BUFFER_DESC lightBufferDesc;
	ZMem(lightBufferDesc);
	lightBufferDesc.ByteWidth = sizeof(Light::LightBufferType) * 100;
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	device->CreateBuffer(&lightBufferDesc, nullptr, &lightBuffer);
	lightBufferDesc.ByteWidth = sizeof(XMFLOAT4);
	device->CreateBuffer(&lightBufferDesc, nullptr, &camPosBuffer);
}

Application::Application()
{
}

Application::~Application()
{
}

void Application::RegisterMeshRenderer(const MeshRenderer* _mr)
{
	renderers.push_back(_mr);
}

void Application::UnRegisterMeshRenderer(const MeshRenderer* _mr)
{
	auto iter = find(renderers.begin(), renderers.end(), _mr);
	if (iter != renderers.end())
		renderers.erase(iter);
}

void Application::RegisterLight(const Light *_light)
{
	lights.push_back(_light);
}

void Application::UnregisterLight(const Light *_light)
{
	auto iter = find(lights.begin(), lights.end(), _light);
	if (iter != lights.end())
		lights.erase(iter);
}

void Application::CreateBuffer(D3D11_BUFFER_DESC* _bData, D3D11_SUBRESOURCE_DATA* _subData, ID3D11Buffer** _buffer) const
{
	device->CreateBuffer(_bData, _subData, _buffer);
}

void Application::Init(HWND& _window)
{
	window = &_window;
	// Create D3D interfaces
	CreateDevice();
	CreateRenderTarget();
	CreateLayout();
	CreateShaders();
	CreateDepthStencil();
	CreateBlendState();
	CreateRasterState();
	CreateCameraAndLightBuffer();
	// Set Initial stuff
	context->IASetInputLayout(layout);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create GameObject
	gameObjectManager.Start();
	gameObjectManager.AddComponent<GameObjectManager>();
}

void Application::Update() const
{
	gameObjectManager.Update();
}

void Application::Render()
{
	//Update light and camera buffers
	Light::LightBufferType lightBuff[100];

	for (size_t i = 0; i < lights.size(); i++)
	{
		lightBuff[i] = lights[i]->GetLightBuffType();
	}

	context->UpdateSubresource(lightBuffer, 0, 0, lightBuff, 0, 0);
	XMFLOAT3 camPos = Camera::mainCam->gameObject->GetComponent<Transform>()->GetWorldPosition();
	context->UpdateSubresource(camPosBuffer, 0, 0, &camPos, 0, 0);

	context->OMSetRenderTargets(1, &screenTargetView, depthStencilView);
	context->ClearRenderTargetView(screenTargetView, backBufferColor);
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	float blendFactor[] = { 1, 1, 1, 1 };
	context->OMSetBlendState(blendState, blendFactor, 0xffffffff);

	Camera* mainCam = Camera::mainCam;
	context->RSSetViewports(1, &mainCam->GetViewport());

	ID3D11Buffer* camBuf = mainCam->GetConstantBuffer();
	context->VSSetConstantBuffers(1, 1, &camBuf);

	ID3D11Buffer* pixBufs[2] = { lightBuffer, camPosBuffer };
	context->PSSetConstantBuffers(0, 2, pixBufs);

	SortMeshesByDistance();

	for (unsigned int i = 0; i < renderers.size(); i++)
		if (renderers[i]->GetType() != MeshRenderer::UI)
			renderers[i]->Render();
	for (unsigned int i = 0; i < renderers.size(); i++)
		if (renderers[i]->GetType() == MeshRenderer::UI)
			renderers[i]->Render();

	swapChain->Present(1, 0);
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
	SAFE_RELEASE(camPosBuffer);
	SAFE_RELEASE(lightBuffer);

	// Shaders
	SAFE_RELEASE(vsMesh);
	SAFE_RELEASE(vsUI);
	SAFE_RELEASE(psMesh);
	SAFE_RELEASE(psSkybox);
	SAFE_RELEASE(psUI);

	gameObjectManager.OnDelete();
}