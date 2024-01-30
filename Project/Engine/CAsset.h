#pragma once

class CAsset
	: public CEntity
{
	using Super = CEntity;

public:
	CAsset(ASSET_TYPE _type);
	virtual ~CAsset();

private:
	wstring				m_strKey;
	wstring				m_strRelativePath;
	int32				m_iRefCnt;	// 스마트 포인터 참조 카운터(Ptr)
	const ASSET_TYPE	m_eType;

public:
	virtual void UpdateData() = 0;
	virtual int Load(const wstring& _strFilePath) { return E_FAIL; }

	const wstring& GetAssetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

private:
	void SetAssetKey(const wstring& _key) { m_strKey = _key; }
	void SetRelativePath(const wstring& _path) { m_strRelativePath = _path; }

	void AddRefCnt() { ++m_iRefCnt; }
	void SubRefCnt() /*{ --m_iRefCnt; }*/
	{
		--m_iRefCnt;
		if (0 >= m_iRefCnt)
			delete this;
	}

	int32 GetRefCount() { return m_iRefCnt; }
	ASSET_TYPE GetAssetType() { return m_eType; }

	void Release()
	{
		--m_iRefCnt;
		if (0 >= m_iRefCnt)
			delete this;
	}

	friend CAssetMgr;

	template <typename T>
	friend class Ptr;
};

