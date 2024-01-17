#pragma once

class CGraphics
	: public CSingleton<CGraphics>
{
	SINGLETON(CGraphics)

private:
	HWND		m_hWnd;
	Vec2		m_v2Resolution;

	float		m_arrClearColor[4];
	bool		m_bStandByMode;

private:
	ComPtr<ID3D11Device>			m_Device;
	ComPtr<ID3D11DeviceContext>		m_Context;
	ComPtr<IDXGISwapChain>			m_SwapChain;

	ComPtr<ID3D11RenderTargetView>	m_RenderTargetView;
	ComPtr<ID3D11DepthStencilView>  m_DepthStencilView;

	CConstantBuffer*				m_arrCB[(uint32)CB_TYPE::END];

public:
	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetContext() { return m_Context.Get(); }
	IDXGISwapChain* GetSwapChain() { return m_SwapChain.Get(); }

	CConstantBuffer* GetConstantBuffer(CB_TYPE _type) { return m_arrCB[(UINT)_type]; }

	Vec2 GetResolution() { return m_v2Resolution; }

public:
	int Init(HWND _hWnd, float _width, float _height);
	void RenderBegin();
	void RenderEnd();

private:
	void SetWindow();
	void DeviceAndSwapChain();
	void RenderTargetView();
	void DepthStencilView();
	void CostantBuffer();
};