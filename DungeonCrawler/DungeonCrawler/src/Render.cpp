#include "Render.h"

Render::Render(HWND hWnd)
{
	// Create Device, Swap Chain, and Immediate Context
	constexpr UINT16 fl_Size = 1;
	D3D_FEATURE_LEVEL featureLevels[fl_Size] = {
		D3D_FEATURE_LEVEL_11_0
	};

	RECT myWinR;
	GetClientRect(hWnd, &myWinR);

	DXGI_MODE_DESC bufferDesc = {};
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
	bufferDesc.Width = myWinR.right - myWinR.left;
	bufferDesc.Height = myWinR.bottom - myWinR.top;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferDesc = bufferDesc;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.BufferCount = 1;
	swapDesc.OutputWindow = hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevels,
		fl_Size,
		D3D11_SDK_VERSION,
		&swapDesc,
		&m_SwapChain,
		&m_Device,
		NULL,
		&m_Context
	);

	// Create Render Target View and Viewport
	ID3D11Resource* backBuffer;
	hr = m_SwapChain->GetBuffer(0, __uuidof(backBuffer), (void**)&backBuffer);
	hr = m_Device->CreateRenderTargetView(
		backBuffer,
		NULL,
		&m_RTV
	);
	backBuffer->Release();

	m_ViewPort.Width = myWinR.right - myWinR.left;
	m_ViewPort.Height = myWinR.bottom - myWinR.top;
	m_ViewPort.TopLeftX = m_ViewPort.TopLeftY = 0;
	m_ViewPort.MinDepth = 0;
	m_ViewPort.MaxDepth = 1;
}

Render::~Render()
{
	m_Device->Release();
	m_SwapChain->Release();
	m_Context->Release();
	m_RTV->Release();
}
