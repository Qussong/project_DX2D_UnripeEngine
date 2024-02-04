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
	wchar_t szExt[20] = {};	// extension : Ȯ����
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);
	
	HRESULT hr = NULL;
	// DDS
	if (!wcscmp(szExt, L".dds") || !wcscmp(szExt, L".DDS"))	// wcscmp()�� ������ 0(false)�� ��ȯ
	{
		hr = LoadFromDDSFile(_strFilePath.c_str(), DDS_FLAGS_NONE, nullptr, m_Image);
	}
	// TGA
	else if (!wcscmp(szExt, L".tga") || !wcscmp(szExt, L".TGA"))
	{
		hr = LoadFromTGAFile(_strFilePath.c_str(), TGA_FLAGS_NONE, nullptr, m_Image);
	}
	// PNG, BMP, JPEG
	else
	{
		// WIC = Windows Imaging Component
		// Loads BMP, PNG, GIF, TIFF, JPEG, and JPEG-XR / HD Photo images
		hr = LoadFromWICFile(_strFilePath.c_str(), WIC_FLAGS_NONE, nullptr, m_Image);
	}

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "Texture Load Failed", "Texture Error", MB_OK);
		return E_FAIL;
	}

	// Shader Resource View ����
	CreateShaderResourceView(DEVICE,
							m_Image.GetImages(),
							m_Image.GetImageCount(),
							m_Image.GetMetadata(),
							m_SRV.GetAddressOf());

	// ������ Resource View�� ���� ID3D11Texture2D ��ü�� ���´�.
	m_SRV->GetResource((ID3D11Resource**)m_Tex2D.GetAddressOf());

	// Texture ��ü�κ��� �ɼ� ������ ���´�.
	m_Tex2D->GetDesc(&m_tDesc);

	return S_OK;
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