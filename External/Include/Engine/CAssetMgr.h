#pragma once

class CAsset;
class CGraphicShader;
class CTexture;

class CAssetMgr
	: public CSingleton<CAssetMgr>
{
	SINGLETON(CAssetMgr);

private:
	map<wstring, CAsset*> m_mapAsset[(UINT)ASSET_TYPE::END];

public:
	void Init();

private:
	void Mesh();
	void Shader();

	template<typename T>
	ASSET_TYPE GetAssetType();

public:
	template<typename T>
	void AddAsset(const wstring& _key, T* _asset);

	template<typename T>
	T* FindAsset(const wstring& _key);

	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath = L"");
};

template<typename T>
inline ASSET_TYPE CAssetMgr::GetAssetType()
{
	const type_info& info = typeid(T);

	ASSET_TYPE type = ASSET_TYPE::END;

	if (&typeid(CMesh) == &info)
		type = ASSET_TYPE::MESH;
	else if (&typeid(CGraphicShader) == &info)
		type = ASSET_TYPE::GRAPHIC_SHADER;
	else if (&typeid(CTexture) == &info)
		type = ASSET_TYPE::TEXTURE;

	return type;
}

template<typename T>
inline void CAssetMgr::AddAsset(const wstring& _key, T* _asset)
{
	ASSET_TYPE type = GetAssetType<T>();

	map<wstring, CAsset*>::iterator iter = m_mapAsset[(UINT)type].find(_key);
	if (m_mapAsset[(UINT)type].end() != iter)
	{
		if(ASSET_TYPE::TEXTURE == type)
			MessageBoxA(nullptr, "Texture Already Loaded", "Add Asset Error", MB_OK);
		else
			MessageBoxA(nullptr, "Asset Already declared", "Add Asset Error", MB_OK);

		_exit(EXIT_FAILURE);
	}

	m_mapAsset[(UINT)type].insert(make_pair(_key, _asset));
}

template<typename T>
inline T* CAssetMgr::FindAsset(const wstring& _key)
{
	ASSET_TYPE type = GetAssetType<T>();

	map<wstring, CAsset*>::iterator iter = m_mapAsset[(UINT)type].find(_key);

	if (m_mapAsset[(UINT)type].end() == iter)
	{
		return nullptr;
	}

	T* asset = (T*)iter->second;
	return asset;
}