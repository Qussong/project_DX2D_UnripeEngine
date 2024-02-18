#pragma once

class CTexture
	: public CAsset
{
	using Super = CAsset;

public:
	CTexture();
	virtual ~CTexture();

private:
	ScratchImage						m_Texture;	// DirectXTex를 통해 로드된 Texture 저장

	D3D11_TEXTURE2D_DESC				m_tDesc;	// Texture 생성 정보
	ComPtr<ID3D11Texture2D>				m_Tex2D;	// Texture 데이터를 GPU 메모리에서 관리
	ComPtr<ID3D11RenderTargetView>		m_RTV;		
	ComPtr<ID3D11DepthStencilView>		m_DSV;
	ComPtr<ID3D11ShaderResourceView>	m_SRV;		// Shader에서 사용하는 용도(Texture Register(t) 바인딩)
	ComPtr<ID3D11UnorderedAccessView>	m_UAV;		// GPGPU(Gernal Purpose GPU), ComputeShader, 읽기/쓰기 동시가능 (Unordered Register(u) 바인딩)

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
	//virtual void UpdateData() override {};	// 사용안함
	void UpdateData(uint32 _iRegisterNum);	// overload
};

