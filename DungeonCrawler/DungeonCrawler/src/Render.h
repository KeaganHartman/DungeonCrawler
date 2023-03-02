#pragma once
#include <iostream>
#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")

// Shader Includes
#include "../shaders/ExamplePixelShader.csh"
#include "../shaders/ExampleVertexShader.csh"

struct ColorVertex
{
	float xyzw[4];
	float rgba[4];
};


class Render
{
public:
	Render(HWND hWnd);
	~Render();
	void RenderLoop();

private:
	ID3D11Device*			m_pDevice;
	IDXGISwapChain*			m_pSwapChain;
	ID3D11DeviceContext*	m_pContext;
	ID3D11RenderTargetView* m_pRenderTargetView;
	D3D11_VIEWPORT			m_ViewPort;
	ID3D11Debug*			m_pDebugger;
	ID3D11Texture2D*		m_pDepthStencilBuffer;
	ID3D11DepthStencilView* m_pDepthStencilView;

	// Drawing a Triangle
	ID3D11Buffer*			m_pTriangleVBuffer;
	ID3D11InputLayout*		m_pInputLayout;
	ID3D11VertexShader*		m_pVShader;
	ID3D11PixelShader*		m_pPShader;
};