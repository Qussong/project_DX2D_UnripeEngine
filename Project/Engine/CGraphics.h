#pragma once
class CGraphics
	: CSingleton<CGraphics>
{
	SINGLETON(CGraphics)

private:
	ComPtr<ID3D11Device>			m_device;
	ComPtr<ID3D11DeviceContext>		m_context;
	ComPtr<IDXGISwapChain>			m_swapChain;
	ComPtr<ID3D11RenderTargetView>	m_renderTargetView;
	D3D11_VIEWPORT					m_viewport;

public:
	void Init(HWND _hWnd);

private:

};

