#include "pch.h"
#include "CAsset.h"

CAsset::CAsset(ASSET_TYPE _type)
	: m_strKey(L"")
	, m_strRelativePath(L"")
	, m_iRefCnt(0)
	, m_eType(_type)
{
	SetName(L"Asset");
}

CAsset::~CAsset()
{
}
