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
	void Material();

	template<typename T>
	ASSET_TYPE GetAssetType();

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath = L"");

	template<typename T>
	void AddAsset(const wstring& _key, T* _asset);

	template<typename T>
	T* FindAsset(const wstring& _key);
};

template<typename T>
inline void CAssetMgr::AddAsset(const wstring& _key, T* _asset)
{
	ASSET_TYPE type = GetAssetType<T>();

	map<wstring, CAsset*>::iterator iter = m_mapAsset[(UINT)type].find(_key);
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

template<typename T>
inline T* CAssetMgr::FindAsset(const wstring& _key)
{
	// Asset Type : MESH, MESHDATA, TEXTURE, MATERIAL,
	//				SOUND, COMPUTE_SHADER, GRAPHIC_SHADER
	ASSET_TYPE type = GetAssetType<T>();

	map<wstring, CAsset*>::iterator iter = m_mapAsset[(UINT)type].find(_key);

	if (m_mapAsset[(UINT)type].end() == iter)
	{
		return nullptr;
	}

	T* asset = (T*)iter->second;
	return asset;
}