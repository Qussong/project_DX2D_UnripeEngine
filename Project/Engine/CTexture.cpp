#include "pch.h"
#include "CTexture.h"

CTexture::CTexture()
	: Super(ASSET_TYPE::TEXTURE)
	, m_tDesc{}
{
	SetName(L"Texture");
}

CTexture::~CTexture()
{
}

int CTexture::Load(const wstring& _strFilePath)
{
	wchar_t szExt[20] = {};	// extension : 확장자
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);
	
	HRESULT hr = NULL;
	// DDS
	if (!wcscmp(szExt, L".dds") || !wcscmp(szExt, L".DDS"))	// wcscmp()는 같으면 0(false)를 반환
	{
		hr = LoadFromDDSFile(_strFilePath.c_str(), DDS_FLAGS_NONE, nullptr, m_Texture);
	}
	// TGA
	else if (!wcscmp(szExt, L".tga") || !wcscmp(szExt, L".TGA"))
	{
		hr = LoadFromTGAFile(_strFilePath.c_str(), TGA_FLAGS_NONE, nullptr, m_Texture);
	}
	// PNG, BMP, JPEG
	else
	{
		// WIC = Windows Imaging Component
		// Loads BMP, PNG, GIF, TIFF, JPEG, and JPEG-XR / HD Photo images
		hr = LoadFromWICFile(_strFilePath.c_str(), WIC_FLAGS_NONE, nullptr, m_Texture);
	}

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "Texture Load Failed", "Texture Error", MB_OK);
		return E_FAIL;
	}

	// Shader Resource View 생성
	CreateShaderResourceView(DEVICE,
							m_Texture.GetImages(),
							m_Texture.GetImageCount(),
							m_Texture.GetMetadata(),
							m_SRV.GetAddressOf());

	// 생성된 Resource View로 부터 ID3D11Texture2D 객체를 얻어온다.
	m_SRV->GetResource((ID3D11Resource**)m_Tex2D.GetAddressOf());

	// Texture 객체로부터 옵션 정보를 얻어온다.
	m_Tex2D->GetDesc(&m_tDesc);

	return S_OK;
}

int CTexture::Create(UINT _width, UINT _height, DXGI_FORMAT _format, UINT _bindFlag, D3D11_USAGE _usage)
{
	HRESULT hr = S_OK;

	// 생성하려는 Texture 설정 세팅
	{
		// Texture 해상도
		m_tDesc.Width = _width;
		m_tDesc.Height = _height;
		// Pixel 포멧
		m_tDesc.Format = _format;
		// 샘플링
		m_tDesc.SampleDesc.Count = 1;
		m_tDesc.SampleDesc.Quality = 0;
		// Texture 용도
		m_tDesc.BindFlags = _bindFlag;
		m_tDesc.Usage  = _usage;
		if (D3D11_USAGE_DYNAMIC == _usage)
		{
			m_tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		// 저퀄리티 버전의 사본 생성여부
		m_tDesc.MipLevels = 1;
		m_tDesc.MiscFlags = 0;
		m_tDesc.ArraySize = 1;
	}
	
	// Texture 생성
	hr = DEVICE->CreateTexture2D(&m_tDesc, nullptr, m_Tex2D.GetAddressOf());
	if (FAILED(hr))
		return E_FAIL;

	// View 생성
	if (m_tDesc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
		hr = DEVICE->CreateDepthStencilView(m_Tex2D.Get(), nullptr, m_DSV.GetAddressOf());
	else if (m_tDesc.BindFlags & D3D11_BIND_RENDER_TARGET)
		hr = DEVICE->CreateRenderTargetView(m_Tex2D.Get(), nullptr, m_RTV.GetAddressOf());
	else if (m_tDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
		hr = DEVICE->CreateShaderResourceView(m_Tex2D.Get(), nullptr, m_SRV.GetAddressOf());
	else if (m_tDesc.BindFlags & D3D11_BIND_UNORDERED_ACCESS)
		hr = DEVICE->CreateUnorderedAccessView(m_Tex2D.Get(), nullptr, m_UAV.GetAddressOf());
	else
		__noop;

	return hr;
}

void CTexture::Clear(uint32 _iRegisterNum)
{
	ID3D11ShaderResourceView* pSRV = nullptr;

	CONTEXT->VSSetShaderResources(_iRegisterNum, 1, &pSRV);
	//CONTEXT->HSSetShaderResources(_iRegisterNum, 1, &pSRV);
	//CONTEXT->DSSetShaderResources(_iRegisterNum, 1, &pSRV);
	//CONTEXT->GSSetShaderResources(_iRegisterNum, 1, &pSRV);
	CONTEXT->PSSetShaderResources(_iRegisterNum, 1, &pSRV);
}

void CTexture::UpdateData(uint32 _iRegisterNum)
{
	CONTEXT->VSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	//CONTEXT->HSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	//CONTEXT->DSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	//CONTEXT->GSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	CONTEXT->PSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
}