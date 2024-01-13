#pragma once

class CMesh;

class CEngine
	: public CSingleton<CEngine>
{
	SINGLETON(CEngine);

private:
	HWND		m_hWnd;

	// Resolution
	int32		 m_iWidth;
	int32		 m_iHeight;

public:
	HWND	GetWindowHandle() { return m_hWnd; }

public:
	int		Init(HWND _hWnd, uint32 _width, uint32 _height);
	void	Progress();
	void	Tick();
	void	Render();

private:
	tTransform					m_tTransform		= { Vec4(0.f, 0.f, 0.f, 1.f), Vec4(1.f, 1.f, 1.f, 1.f) };
	Vtx							m_arrRect[4]		= {};
	UINT						m_arrIdx[6]			= {};

	CMesh*						m_RectMesh = nullptr;

	ComPtr<ID3D11InputLayout>	m_Layout;		// InputLayout
	ComPtr<ID3DBlob>			m_VSBlob;		// VertexShaderBlob
	ComPtr<ID3D11VertexShader>	m_VS;			// VertexShader
	ComPtr<ID3DBlob>			m_PSBlob;		// PixelShaderBlob
	ComPtr<ID3D11PixelShader>	m_PS;			// PixelShader
	ComPtr<ID3DBlob>			m_ErrBlob;		// ErrorBlob
	ComPtr<ID3D11Buffer>		m_CB;			// ConstantBuffer

public:
	void Test_init();
	void Test_tick();
	void Test_render();
};

