#pragma once

class CEngine
	: public CSingleton<CEngine>
{
	SINGLETON(CEngine);

private:
	HWND				m_hWnd;
	unsigned __int32	m_width;
	unsigned __int32	m_height;
	bool				m_bStandByMode = false;

private:
	//ComPtr<ID3D11Device>			m_device;
	//ComPtr<ID3D11DeviceContext>		m_context;
	//ComPtr<IDXGISwapChain>			m_swapChain;
	//ComPtr<ID3D11RenderTargetView>	m_renderTargetView;
	//D3D11_VIEWPORT					m_viewport;

public:
	int Init(HWND _hWnd);
	void Update();
	void Render();

private:
	void RenderBegin();
	void RenderEnd();
	void DeviceAndSwapChain();
	void RenderTargetView();
	void SetViewport();
};

