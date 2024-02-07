#pragma once

class CGraphics
	: public CSingleton<CGraphics>
{
	SINGLETON(CGraphics)

private:
	HWND		m_hWnd;
	Vec2		m_v2Resolution;
	bool		m_bStandByMode;

private:
	ComPtr<ID3D11Device>			m_Device;
	ComPtr<ID3D11DeviceContext>		m_Context;
	ComPtr<IDXGISwapChain>			m_SwapChain;
	ComPtr<ID3D11Texture2D>			m_RenderTarget;	// = RenderTargetTexture
	ComPtr<ID3D11RenderTargetView>	m_RenderTargetView;

	ComPtr<ID3D11Texture2D>			m_DepthStencil;
	ComPtr<ID3D11DepthStencilView>	m_DepthStencilView;
	//Ptr<CTexture>					m_DepthStencilTexture;

	CConstantBuffer*				m_arrCB[(uint32)CB_TYPE::END];
	ComPtr<ID3D11RasterizerState>	m_arrRS[(UINT)RS_TYPE::END];
	ComPtr<ID3D11DepthStencilState>	m_arrDS[(UINT)DS_TYPE::END];
	ComPtr<ID3D11BlendState>		m_arrBS[(UINT)DS_TYPE::END];
	ComPtr<ID3D11SamplerState>		m_arrSS[(UINT)SS_TYPE::END];

public:
	ID3D11Device*					GetDevice()					{ return m_Device.Get(); }
	ID3D11DeviceContext*			GetContext()				{ return m_Context.Get(); }
	IDXGISwapChain*					GetSwapChain()				{ return m_SwapChain.Get(); }
	Vec2							GetResolution()				{ return m_v2Resolution; }
	CConstantBuffer*				GetCB(CB_TYPE _type)		{ return m_arrCB[(UINT)_type]; }
	ComPtr<ID3D11RasterizerState>	GetRSState(RS_TYPE _Type)	{ return m_arrRS[(UINT)_Type]; }
	ComPtr<ID3D11DepthStencilState> GetDSState(DS_TYPE _Type)	{ return m_arrDS[(UINT)_Type]; }
	ComPtr<ID3D11BlendState>		GetBSState(BS_TYPE _Type)	{ return m_arrBS[(UINT)_Type]; }

private:
	void	SetWindow();
	void	DeviceAndSwapChain();
	void	RenderTargetView();
	void	DepthStencilView();
	void	CostantBuffer();
	int		RasterizerState();
	int		DepthStencilState();
	int		BlendState();
	int		SamplerState();

public:
	void	ClearRenderTarget(Vec4 _color);

public:
	int		Init(HWND _hWnd, float _width, float _height);
	void	RenderBegin();
	void	RenderEnd();

};