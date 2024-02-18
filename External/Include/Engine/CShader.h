#pragma once

//class CAsset;
#include "CAsset.h";

class CShader
	: public CAsset
{
	using Super = CAsset;

public:
	CShader(ASSET_TYPE _type);
	virtual ~CShader();
	
protected:
	ComPtr<ID3DBlob>	m_ErrBlob;	// ErrorBlob

public:
	virtual void UpdateData() = 0;
};