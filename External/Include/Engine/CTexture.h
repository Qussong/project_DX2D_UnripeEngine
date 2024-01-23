#pragma once

class CTexture
	: public CAsset
{
	using Super = CAsset;

public:
	CTexture();
	virtual ~CTexture();

private:
	ScratchImage						m_Image;	// DirectXTex�� ���� �ε�� Texture ����

	D3D11_TEXTURE2D_DESC				m_tDesc;	// Texture ���� ����
	ComPtr<ID3D11Texture2D>				m_Tex2D;	// Texture �����͸� GPU �޸𸮿��� ����

	ComPtr<ID3D11RenderTargetView>		m_RTV;		
	ComPtr<ID3D11DepthStencilView>		m_DSV;
	ComPtr<ID3D11ShaderResourceView>	m_SRV;		// Shader���� ����ϴ� �뵵(Texture Register(t) ���ε�)
	ComPtr<ID3D11UnorderedAccessView>	m_UAV;		// GPGPU(Gernal Purpose GPU), ComputeShader, �б�/���� ���ð��� (Unordered Register(u) ���ε�)

public:
	virtual void UpdateData() override {};
	virtual void UpdateData(uint32 _iRegisterNum);	// overload
	virtual int Load(const wstring& _strFilePath) override;
};
