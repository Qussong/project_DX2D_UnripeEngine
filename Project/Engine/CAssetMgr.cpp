#include "pch.h"
#include "CAssetMgr.h"

CAssetMgr::CAssetMgr()
{
}

CAssetMgr::~CAssetMgr()
{
}



Ptr<CTexture> CAssetMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = nullptr;
	pTex = FindAsset<CTexture>(_strKey).Get();

	// �Է��� Key ������ �̹� �ٸ� Texture ������ ���
	if (nullptr != pTex)
		return pTex;

	wstring strFilePath = M_PATH->GetResourcetPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	if (FAILED(pTex->Load(strFilePath)))
	{
		MessageBoxA(nullptr, "Texture Load Failed", "Asset Error", MB_OK);
		pTex = nullptr;
		return nullptr;
	}

	pTex->SetName(_strKey);
	pTex->SetAssetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);
	AddAsset(_strKey, pTex);

	return pTex;
}

Ptr<CTexture> CAssetMgr::CreateTexture(const wstring& _key, UINT _width, UINT _height,
										DXGI_FORMAT _format, UINT _bindFlag, D3D11_USAGE _usage)
{
	Ptr<CTexture> pTex = nullptr;

	// �̹� �����ϴ� Ű������ Ȯ��
	pTex = FindAsset<CTexture>(_key);
	if (nullptr != pTex)
	{
		MessageBoxA(nullptr, "Already Exist Key", "CAssetMgr Error", MB_OK);
		_exit(EXIT_FAILURE);
	}

	// Texture ����
	pTex = new CTexture;
	HRESULT hr = pTex->Create(_width, _height, _format, _bindFlag, _usage);
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "Texture Create Failed", "CAssetMgr Error", MB_OK);
		return nullptr;
	}

	// ������ Texture ����
	AddAsset<CTexture>(_key, pTex.Get());

	return pTex;
}

Ptr<CTexture> CAssetMgr::CreateTexture(const wstring& _key, ComPtr<ID3D11Texture2D> _tex2D)
{
	Ptr<CTexture> pTex = nullptr;

	// �̹� �����ϴ� Ű������ Ȯ��
	pTex = FindAsset<CTexture>(_key);
	if (nullptr != pTex)
	{
		MessageBoxA(nullptr, "Already Exist Key", "CAssetMgr Error", MB_OK);
		_exit(EXIT_FAILURE);
	}

	// Texture ����
	pTex = new CTexture;
	HRESULT hr = pTex->Create(_tex2D);
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "Texture Create Failed", "CAssetMgr Error", MB_OK);
		return nullptr;
	}

	// ������ Texture ����
	AddAsset<CTexture>(_key, pTex.Get());

	return pTex;
}