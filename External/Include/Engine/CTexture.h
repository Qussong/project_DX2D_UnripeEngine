#pragma once

class CTexture
	: public CAsset
{
	using Super = CAsset;

public:
	CTexture();
	virtual ~CTexture();

private:
	ScratchImage						m_Image;	// DirectXTex를 통해 로드된 Texture 저장

	D3D11_TEXTURE2D_DESC				m_tDesc;	// Texture 생성 정보
	ComPtr<ID3D11Texture2D>				m_Tex2D;	// Texture 데이터를 GPU 메모리에서 관리

	ComPtr<ID3D11RenderTargetView>		m_RTV;		
	ComPtr<ID3D11DepthStencilView>		m_DSV;
	ComPtr<ID3D11ShaderResourceView>	m_SRV;		// Shader에서 사용하는 용도(Texture Register(t) 바인딩)
	ComPtr<ID3D11UnorderedAccessView>	m_UAV;		// GPGPU(Gernal Purpose GPU), ComputeShader, 읽기/쓰기 동시가능 (Unordered Register(u) 바인딩)

public:
	virtual void UpdateData() override {};
	virtual void UpdateData(uint32 _iRegisterNum);	// overload
	virtual int Load(const wstring& _strFilePath) override;
	
public:
	static void Clear(uint32 _iRegisterNum);
};

