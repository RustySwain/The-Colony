#include "Application.h"
#include "Macros.h"
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

	//Buffer for light View and Proj matrices
	lightBufferDesc.ByteWidth = sizeof(Light::LightMatrices) * 100;
	device->CreateBuffer(&lightBufferDesc, nullptr, &lightMatricesBuffer);

	lightBufferDesc.ByteWidth = sizeof(XMFLOAT4) * 100;
	device->CreateBuffer(&lightBufferDesc, nullptr, &lightPositionBuffer);
}

void Application::CreateDepthAndTextureClass()
{
	_RenderTexture = new RenderTexture();
	_RenderTexture->Initialize(device, SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);

	_Depth = new Depth();
	_Depth->Initialize(device);

	D3D11_SAMPLER_DESC samplerDesc;
	// Create a wrap texture sampler state description.
	samplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	device->CreateSamplerState(&samplerDesc, &_sampleStateWrap);
}

void Application::UpdateLightResources()
{
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
	renderers.erase(iter);
}

void Application::RegisterLight(const Light *_light)
{
	lights.push_back(_light);
}

void Application::UnregisterLight(const Light *_light)
{
	auto iter = find(lights.begin(), lights.end(), _light);
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
	CreateDepthAndTextureClass();
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
	//Shadow mapping render pass
	ID3D11ShaderResourceView* pNullSRV = nullptr;
	context->PSSetShaderResources(4, 1, &pNullSRV);

	ID3D11RenderTargetView* nullRTV = nullptr;
	context->OMSetRenderTargets(1, &nullRTV, nullptr);

	RenderSceneToTexture();

	// Set the sampler states in the pixel shader.
	context->PSSetSamplers(1, 1, &_sampleStateWrap);

	//Update light and camera buffers
	Light::LightBufferType lightBuff[100];
	vector<const Light*> lightsToAdd;
	for (size_t i = 0; i < lights.size(); i++)
		if (lights[i]->GetEnabled())
			lightsToAdd.push_back(lights[i]);

	for (size_t i = 0; i < lightsToAdd.size(); i++)
	{
		//lights.size can be zero if game is in main menu
		if (lights.size() > 0)
		{
			lightBuff[i] = lightsToAdd[i]->GetLightBuffType();
			if (lights[i]->type == 2)
			{
				lightMat = lights[i]->GetLightMatrices();
				XMFLOAT3 p = lights[i]->gameObject->GetComponent<Transform>()->GetWorldPosition();
				XMFLOAT4 lightPos = XMFLOAT4(p.x, p.y, p.z, 0);
				context->UpdateSubresource(lightMatricesBuffer, 0, 0, &lightMat, 0, 0);
				context->UpdateSubresource(lightPositionBuffer, 0, 0, &lightPos, 0, 0);
			}
		}
	}

	//Updating Light and Camera Buffer
	context->UpdateSubresource(lightBuffer, 0, 0, lightBuff, 0, 0);
	XMFLOAT3 camPos = Camera::mainCam->gameObject->GetComponent<Transform>()->GetWorldPosition();
	context->UpdateSubresource(camPosBuffer, 0, 0, &camPos, 0, 0);

	//Setting and Clearing Render Targets and Depth Stencil before drawing to them
	context->OMSetRenderTargets(1, &screenTargetView, depthStencilView);
	context->ClearRenderTargetView(screenTargetView, backBufferColor);
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->IASetInputLayout(layout);

	//Aplha blending for transparency
	float blendFactor[] = { 1, 1, 1, 1 };
	context->OMSetBlendState(blendState, blendFactor, 0xffffffff);

	//Setting Viewport
	Camera* mainCam = Camera::mainCam;
	context->RSSetViewports(1, &mainCam->GetViewport());

	//Setting constant buffers
	ID3D11Buffer* camBuf = mainCam->GetConstantBuffer();
	context->VSSetConstantBuffers(1, 1, &camBuf);
	context->VSSetConstantBuffers(3, 1, &lightMatricesBuffer);
	context->VSSetConstantBuffers(4, 1, &lightPositionBuffer);

	ID3D11Buffer* pixBufs[2] = { lightBuffer, camPosBuffer };
	context->PSSetConstantBuffers(0, 2, pixBufs);

	depthBufferTexture = _RenderTexture->GetShaderResourceView();
	context->PSSetShaderResources(4, 1, &depthBufferTexture);

	SortMeshesByDistance();
	for (unsigned int i = 0; i < renderers.size(); i++)
		if (renderers[i]->GetType() != MeshRenderer::UI && renderers[i]->GetEnabled())
			renderers[i]->Render();

	for (unsigned int i = 0; i < renderers.size(); i++)
		if (renderers[i]->GetType() == MeshRenderer::UI && renderers[i]->GetEnabled())
			renderers[i]->Render();

	swapChain->Present(vsync, 0);
}

void Application::RenderSceneToTexture()
{
	XMMATRIX worldMatrix, lightViewMatrix, lightProjectionMatrix, translateMatrix;

	for (size_t i = 0; i < lights.size(); i++)
	{
		if (lights.size() != 0 && lights[i]->type == 2)
		{
			// Set the render target to be the render to texture.
			_RenderTexture->SetRenderTarget(context);

			//Clear the render to texture.
			_RenderTexture->ClearRenderTarget(context, 0.0f, 0.0f, 0.0f, 1.0f);

			Light::LightMatrices lmatrices = lights[i]->GetLightMatrices();

			// Render the cube model with the depth shader.
			SortMeshesByDistance();

			//i starts at 1 because renderers[0] = skybox
			/*for (size_t i = 1; i < renderers.size(); i++)
			{*/
			renderers[3]->RenderShadow();
			_Depth->Render(context, renderers[3]->GetIndexCount(), 1, renderers[3]->gameObject->GetComponent<Transform>()->GetWorldMatrix(), lmatrices.lightView, lmatrices.lightProj);
			//}
			XMFLOAT3 p = lights[i]->gameObject->GetComponent<Transform>()->GetWorldPosition();
			XMFLOAT4 lightPos = XMFLOAT4(p.x, p.y, p.z, 0);

			_RenderTexture->ClearScreen(context);
		}
	}
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
	SAFE_RELEASE(lightMatricesBuffer);
	SAFE_RELEASE(lightPositionBuffer);
	// Shaders
	SAFE_RELEASE(vsMesh);
	SAFE_RELEASE(vsUI);
	SAFE_RELEASE(psMesh);
	SAFE_RELEASE(psSkybox);
	SAFE_RELEASE(psUI);

	SAFE_RELEASE(_sampleStateWrap);

	_Depth->Shutdown();
	_RenderTexture->Shutdown();
	delete _Depth;
	delete _RenderTexture;

	//SAFE_RELEASE(depthBufferTexture);

	gameObjectManager.OnDelete();
}