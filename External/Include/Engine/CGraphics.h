#pragma once
class CGraphics
	: public CSingleton<CGraphics>
{
	SINGLETON(CGraphics)

private:
	HWND		m_hWnd;
	uint32		m_width;
	uint32		m_height;

	float		m_clearColor[4];
	bool		m_bStandByMode;


private:
	ComPtr<ID3D11Device>			m_device;
	ComPtr<ID3D11DeviceContext>		m_context;
	ComPtr<IDXGISwapChain>			m_swapChain;

	ComPtr<ID3D11RenderTargetView>	m_renderTargetView;
	ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

public:
	int Init(HWND _hWnd, uint32 _width, uint32 _height);

	ID3D11Device* GetDevice() { return m_device.Get(); }
	ID3D11DeviceContext* GetContext() { return m_context.Get(); }
	IDXGISwapChain* GetSwapChain() { return m_swapChain.Get(); }

	void RenderBegin();
	void RenderEnd();

private:

	void SetWindow();
	void DeviceAndSwapChain();
	void RenderTargetView();
	void DepthStencilView();

	// test
	void TestKey();
};