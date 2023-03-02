#include "Render.h"
Render::Render(HWND hWnd)
{
#pragma region D3D11 Initialization
	// Create Device, Swap Chain, and Immediate Context
	constexpr UINT16 fl_Size = 6;
	D3D_FEATURE_LEVEL featureLevels[fl_Size] = {D3D_FEATURE_LEVEL_11_0,
												D3D_FEATURE_LEVEL_10_1,
												D3D_FEATURE_LEVEL_10_0,
												D3D_FEATURE_LEVEL_9_3,
												D3D_FEATURE_LEVEL_9_2,
												D3D_FEATURE_LEVEL_9_1}; 

	RECT myWinR;
	GetClientRect(hWnd, &myWinR);

	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferDesc.Width = myWinR.right - myWinR.left;
	swapDesc.BufferDesc.Height = myWinR.bottom - myWinR.top;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.BufferCount = 1;
	swapDesc.OutputWindow = hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain( NULL,
										D3D_DRIVER_TYPE_HARDWARE,
										NULL,
										D3D11_CREATE_DEVICE_DEBUG,
										featureLevels,
										fl_Size,
										D3D11_SDK_VERSION,
										&swapDesc,
										&m_pSwapChain,
										&m_pDevice,
										NULL,
										&m_pContext );

	// Error Checking Macro
	if (FAILED(hr))
	{
		std::cout << "Failed to Create Device and Swapchain!\n";
		system("pause");
	}

	// Extract BackBuffer and Debugger
	ID3D11Texture2D* pSwapChainBuffer = 0;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(pSwapChainBuffer), (void**)&pSwapChainBuffer);

	m_pDebugger = 0;
	hr = m_pDevice->QueryInterface(__uuidof(ID3D11Debug), (void**)&m_pDebugger);
#pragma endregion

	// Create Render Target View to allow binding of swap chain texture
	hr = m_pDevice->CreateRenderTargetView( pSwapChainBuffer,
											NULL,
											&m_pRenderTargetView);
	pSwapChainBuffer->Release();

	// Create a Depth Stencil Buffer and Depth Stencil View
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = myWinR.right - myWinR.left;
	desc.Height = myWinR.bottom - myWinR.top;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D32_FLOAT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	hr = m_pDevice->CreateTexture2D(&desc, 0, &m_pDepthStencilBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc;
	ZeroMemory(&dsv_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

	//hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &dsv_desc, &m_pDepthStencilView);

	// Initialize Viewport
	m_ViewPort.Width = myWinR.right - myWinR.left;
	m_ViewPort.Height = myWinR.bottom - myWinR.top;
	m_ViewPort.TopLeftX = m_ViewPort.TopLeftY = 0;
	m_ViewPort.MinDepth = 0;
	m_ViewPort.MaxDepth = 1;

	// Load Triangle -- Create Buffer that Points to Triangle
	ColorVertex triangle[] =
	{	// Position				// Color
		{{0, 0.5f, 0, 1},		{1,0,0,1}},
		{{0.5f, -0.5f, 0, 1},	{0,1,0,1}},
		{{-0.5f, -0.5f, 0, 1},	{0,0,1,1}}
	};

	D3D11_BUFFER_DESC bDesc;

	ZeroMemory(&bDesc, sizeof(D3D11_BUFFER_DESC));
	bDesc.ByteWidth = sizeof(triangle);
	bDesc.Usage = D3D11_USAGE_DEFAULT;
	bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bDesc.CPUAccessFlags = 0;
	bDesc.MiscFlags = 0;
	bDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subData;

	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = triangle;
	
	hr = m_pDevice->CreateBuffer(&bDesc, &subData, &m_pTriangleVBuffer);

	// Create Vertex and Pixel Shaders
	hr = m_pDevice->CreateVertexShader(	ExampleVertexShader, 
										sizeof(ExampleVertexShader), 
										nullptr, 
										&m_pVShader);

	hr = m_pDevice->CreatePixelShader(	ExamplePixelShader, 
										sizeof(ExamplePixelShader), 
										nullptr, 
										&m_pPShader);

	// Create Input Layout
	D3D11_INPUT_ELEMENT_DESC ieDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	hr = m_pDevice->CreateInputLayout(ieDesc, 2, ExampleVertexShader, sizeof(ExampleVertexShader), &m_pInputLayout);
}

Render::~Render()
{
	m_pDevice->Release();
	m_pSwapChain->Release();
	m_pContext->Release();
	m_pRenderTargetView->Release();
	m_pDebugger->Release();
	m_pDepthStencilBuffer->Release();
	//m_pDepthStencilView->Release();

	// Release Triangle
	m_pTriangleVBuffer->Release();
	m_pInputLayout->Release();
	m_pVShader->Release();
	m_pPShader->Release();
}

void Render::RenderLoop()
{
	float color[] = { 0,1,1,1 };
	m_pContext->ClearRenderTargetView(m_pRenderTargetView, color);


	ID3D11RenderTargetView* tempRTV[] = { m_pRenderTargetView };
	m_pContext->OMSetRenderTargets(1, tempRTV, nullptr);
	m_pContext->RSSetViewports(1, &m_ViewPort);
	m_pContext->IASetInputLayout(m_pInputLayout);
	UINT strides[] = {sizeof(ColorVertex)};
	UINT offsets[] = {0};
	ID3D11Buffer* tempVB[] = { m_pTriangleVBuffer };
	m_pContext->IASetVertexBuffers(0, 1, tempVB, strides, offsets);
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pContext->VSSetShader(m_pVShader, 0, 0);
	m_pContext->PSSetShader(m_pPShader, 0, 0);


	
	m_pContext->Draw(3, 0);
	m_pSwapChain->Present(0, 0);
}

