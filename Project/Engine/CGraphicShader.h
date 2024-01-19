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
	D3D11_PRIMITIVE_TOPOLOGY	m_Topology;	// default = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST

	ComPtr<ID3DBlob>			m_VSBlob;	// Vertex Shader Blob
	ComPtr<ID3DBlob>			m_PSBlob;	// Pixel Shader Blob

	ComPtr<ID3D11VertexShader>	m_VS;		// Vertex Shader
	ComPtr<ID3D11PixelShader>	m_PS;		// Pixel Shader

	RS_TYPE                     m_eRSType;	// Rasterizer State
	DS_TYPE                     m_eDSType;	// DepthStencil State
	BS_TYPE                     m_eBSType;	// Blend State

private:
	// Layout ����
	// Layout ������ VSBlob �� ���� ������ �ʿ��ϴ�.
	void Layout();

public:
	virtual void UpdateData() override;

public:
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _topology) { m_Topology = _topology; }
	// Vertex Shader ����
	void VertexShader(const wstring& _fileName,
						const string& _function,
						const string& _version = "vs_5_0");
	// Pixel Shader ����
	void PixelShader(const wstring& _fileName,
						const string& _function,
						const string& _version = "ps_5_0");	
	void SetRSType(RS_TYPE _type) { m_eRSType = _type; }
	void SetDSType(DS_TYPE _type) { m_eDSType = _type; }
	void SetBSType(BS_TYPE _type) { m_eBSType = _type; }
};

