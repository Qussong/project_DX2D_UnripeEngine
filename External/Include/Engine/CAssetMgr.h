#pragma once

class CAsset;
class CGraphicShader;
class CTexture;

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
	void Texture();

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
};

template <typename T>
inline void CAssetMgr::AddAsset(const wstring& _key, T* _asset)
{
	ASSET_TYPE type = GetAssetType<T>();

	map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)type].find(_key);

	// �̹� m_mapAsset�� �ش��ϴ� Ű ������ Asset�� ����Ǿ� �ִ°��
	if (m_mapAsset[(UINT)type].end() != iter)
	{
		if (ASSET_TYPE::TEXTURE == type)
			MessageBoxA(nullptr, "Texture Already Loaded", "Add Asset Error", MB_OK);
		else
			MessageBoxA(nullptr, "Asset Already declared", "Add Asset Error", MB_OK);

		_exit(EXIT_FAILURE);
	}
	// �ش��ϴ� Ű������ Asset�� ����Ǿ� ���� �������
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

	// �Է��� Key ������ �̹� �ٸ� Asset ������ ���
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
