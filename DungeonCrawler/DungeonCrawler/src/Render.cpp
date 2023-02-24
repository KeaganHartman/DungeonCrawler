#include "Render.h"

Render::Render(HWND hWnd)
{
	// Create Device and Swap Chain
	constexpr UINT16 fl_Size = 1;
	D3D_FEATURE_LEVEL featureLevels[fl_Size] = {
		D3D_FEATURE_LEVEL_11_0
	};

	RECT myWinR;
	GetClientRect(hWnd, &myWinR);

	DXGI_MODE_DESC bufferDesc = {};
	bufferDesc.Width = myWinR.right - myWinR.left;
	bufferDesc.Height = myWinR.bottom - myWinR.top;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapDesc.BufferDesc = bufferDesc;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapDesc.BufferCount = 1;
	swapDesc.OutputWindow = hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = 0;

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

	return;
}
