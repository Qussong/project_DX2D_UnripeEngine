#pragma once

class CTexture
	: public CAsset
{
	using Super = CAsset;

public:
	CTexture();
	virtual ~CTexture();

private:
	ScratchImage						m_Texture;	// DirectXTex�� ���� �ε�� Texture ����

	D3D11_TEXTURE2D_DESC				m_tDesc;	// Texture ���� ����
	ComPtr<ID3D11Texture2D>				m_Tex2D;	// Texture �����͸� GPU �޸𸮿��� ����
	ComPtr<ID3D11RenderTargetView>		m_RTV;		
	ComPtr<ID3D11DepthStencilView>		m_DSV;
	ComPtr<ID3D11ShaderResourceView>	m_SRV;		// Shader���� ����ϴ� �뵵(Texture Register(t) ���ε�)
	ComPtr<ID3D11UnorderedAccessView>	m_UAV;		// GPGPU(Gernal Purpose GPU), ComputeShader, �б�/���� ���ð��� (Unordered Register(u) ���ε�)

public:
	// Getter
	const UINT							GetWidth()	{ return m_tDesc.Width; }
	const UINT							GetHeight() { return m_tDesc.Height; }
	ComPtr<ID3D11Texture2D>				GetTex2D()	{ return m_Tex2D; }
	ComPtr<ID3D11RenderTargetView>		GetRTV()	{ return m_RTV; }
	ComPtr<ID3D11DepthStencilView>		GetDSV()	{ return m_DSV; }
	ComPtr<ID3D11ShaderResourceView>	GetSRV()	{ return m_SRV; }
	ComPtr<ID3D11UnorderedAccessView>	GetUAV()	{ return m_UAV; }
	
public:
	int Create(UINT _width,
				UINT _height,
				DXGI_FORMAT _format,
				UINT _bindFlag,
				D3D11_USAGE _usage = D3D11_USAGE_DEFAULT);
	int Create(ComPtr<ID3D11Texture2D> _origin);
	static void Clear(uint32 _iRegisterNum);

public:
	virtual int Load(const wstring& _strFilePath) override;
	//virtual void UpdateData() override {};	// ������
	void UpdateData(uint32 _iRegisterNum);	// overload
};

