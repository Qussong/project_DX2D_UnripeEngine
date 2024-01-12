#pragma once

class CEngine
	: public CSingleton<CEngine>
{
	SINGLETON(CEngine);

private:
	HWND		m_hWnd;

	// Resolution
	int32		 m_width;
	int32		 m_height;

public:
	HWND GetWindowHandle() { return m_hWnd; }

public:
	int Init(HWND _hWnd, uint32 _width, uint32 _height);
	void Progress();
	void Tick();
	void Render();

private:
	cTransform					m_transform		= { Vec4(0.f, 0.f, 0.f, 1.f), Vec4(1.f, 1.f, 1.f, 1.f) };
	Vtx							m_rectangle[4]	= {};
	UINT						m_idx[6]		= {};

	ComPtr<ID3D11Buffer>		m_VB;			// VertexBuffer
	ComPtr<ID3D11Buffer>		m_IB;			// IndexBuffer
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

