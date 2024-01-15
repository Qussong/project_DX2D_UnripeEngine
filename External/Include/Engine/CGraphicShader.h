#pragma once

class CGraphicShader
	: public CShader
{
	using Super = CShader;

public:
	CGraphicShader();
	~CGraphicShader();

private:
	ComPtr<ID3D11InputLayout>	m_Layout;		
	D3D11_PRIMITIVE_TOPOLOGY	m_Topology;		// default = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST

	ComPtr<ID3DBlob>			m_VSBlob;		// VertexShaderBlob
	ComPtr<ID3DBlob>			m_PSBlob;		// PixelShaderBlob

	ComPtr<ID3D11VertexShader>	m_VS;			// VertexShader
	ComPtr<ID3D11PixelShader>	m_PS;			// PixelShader

private:
	// Layout 持失
	void Layout();

public:
	virtual void UpdateData() override;

public:
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _topology) { m_Topology = _topology; }

	// Vertex Shader 持失
	void VertexShader(const wstring& _fileName, const string& _function, const string& _version = "vs_5_0");
	// Pixel Shader 持失
	void PixelShader(const wstring& _fileName, const string& _function, const string& _version = "ps_5_0");	
};

