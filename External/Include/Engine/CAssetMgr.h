#pragma once

class CAsset;
class CMesh;
class CGraphicShader;
class CTexture;
class CMaterial;

class CAssetMgr
	: public CSingleton<CAssetMgr>
{
	SINGLETON(CAssetMgr);

private:
	map<wstring, Ptr<CAsset>> m_mapAsset[(UINT)ASSET_TYPE::END];

public:
	void Init();

private:
	void Mesh();
	void Shader();
	void Material();
	void Texture();		// 공용이미지 로드

	template<typename T>
	ASSET_TYPE GetAssetType();

public:
	template <typename T>
	void AddAsset(const wstring& _key, T* _asset);

	template <typename T>
	Ptr<T> FindAsset(const wstring& _key);

	template <typename T>
	Ptr<T> Load(const wstring& _key, const wstring& _strRelativePath);

	Ptr<CTexture> LoadTexture(const wstring& _strKey, const wstring& _strRelativePath = L"");

	Ptr<CTexture> CreateTexture(const wstring& _key, UINT _width, UINT _height, DXGI_FORMAT _format, UINT _bindFlag, D3D11_USAGE _usage = D3D11_USAGE_DEFAULT);
	Ptr<CTexture> CreateTexture(const wstring& _key, ComPtr<ID3D11Texture2D> _tex2D);
};

template<typename T>
ASSET_TYPE CAssetMgr::GetAssetType()
{
	const type_info& info = typeid(T);

	ASSET_TYPE type = ASSET_TYPE::END;

	if (&typeid(CMesh) == &info)
		type = ASSET_TYPE::MESH;
	else if (&typeid(CGraphicShader) == &info)
		type = ASSET_TYPE::GRAPHIC_SHADER;
	else if (&typeid(CTexture) == &info)
		type = ASSET_TYPE::TEXTURE;
	else if (&typeid(CMaterial) == &info)
		type = ASSET_TYPE::MATERIAL;

	return type;
}

template <typename T>
inline void CAssetMgr::AddAsset(const wstring& _key, T* _asset)
{
	ASSET_TYPE type = GetAssetType<T>();

	map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)type].find(_key);

	// 이미 m_mapAsset에 해당하는 키 값으로 Asset이 저장되어 있는경우
	if (m_mapAsset[(UINT)type].end() != iter)
	{
		if (ASSET_TYPE::TEXTURE == type)
			MessageBoxA(nullptr, "Texture Already Loaded", "Add Asset Error", MB_OK);
		else
			MessageBoxA(nullptr, "Asset Already declared", "Add Asset Error", MB_OK);

		_exit(EXIT_FAILURE);
	}
	// 해당하는 키값으로 Asset이 저장되어 있지 않은경우
	else
	{
		m_mapAsset[(UINT)type].insert(make_pair(_key, _asset));
	}
}

template <typename T>
inline Ptr<T> CAssetMgr::FindAsset(const wstring& _key)
{
	// Asset Type : MESH, MESHDATA, TEXTURE, MATERIAL,
	//				SOUND, COMPUTE_SHADER, GRAPHIC_SHADER
	ASSET_TYPE type = GetAssetType<T>();

	map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)type].find(_key);

	if (m_mapAsset[(UINT)type].end() == iter)
		return nullptr;

	return (T*)iter->second.Get();
}

template<typename T>
inline Ptr<T> CAssetMgr::Load(const wstring& _key, const wstring& _strRelativePath)
{
	Ptr<T> pAsset = nullptr;
	pAsset = FindAsset<T>(_key);

	// 입력한 Key 값으로 이미 다른 Asset 존재할 경우
	if (nullptr != pAsset)
		return pAsset;

	pAsset = new T;
	wstring strFilePath = M_PATH->GetResourcetPath();
	strFilePath += _strRelativePath;

	HRESULT hr = pAsset->Load(strFilePath);
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "Load Asset Failed", "Asset Error", MB_OK);
		pAsset = nullptr;
		return nullptr;
	}

	pAsset->SetAssetKey(_key);
	pAsset->SetRelativePath(_strRelativePath);
	AddAsset<T>(_key, pAsset.Get());

	return pAsset;
}
