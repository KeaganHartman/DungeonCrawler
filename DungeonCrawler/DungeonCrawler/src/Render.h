#pragma once
#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")

class Render
{
public:
	Render(HWND hWnd);
	~Render();

private:
	ID3D11Device*			m_Device = {};
	IDXGISwapChain*			m_SwapChain = {};
	ID3D11DeviceContext*	m_Context = {};
	ID3D11RenderTargetView* m_RTV = {};
	D3D11_VIEWPORT			m_ViewPort = {};
};

