#include "pch.h"
#include "CMaterial.h"

CMaterial::CMaterial()
	: Super(ASSET_TYPE::MATERIAL)
	, m_tMtrlConst{}
	, m_arrTex{}
	, m_pShader(nullptr)
{
	SetName(L"Material");
}

CMaterial::~CMaterial()
{
}

void CMaterial::UpdateData()
{
	if (nullptr == m_pShader.Get())
		return;

	// Shader Binding
	m_pShader->UpdateData();

	// Texture Binding
	for (UINT i = 0; i < (UINT)TEX_PARAM::END; ++i)
	{
		// Texture 데이터가 들어있는 경우
		if (nullptr != m_arrTex[i].Get())
		{
			m_arrTex[i]->UpdateData(i);
			m_tMtrlConst.bTex[i] = (int32)true;		// 1
		}
		// Texture 데이터가 들어있지 않은 경우
		else
		{
			CTexture::Clear(i);
			m_tMtrlConst.bTex[i] = (int32)false;	// 0
		}
	}

	// Material 상수버퍼 업데이트
	static CConstantBuffer* pCB = GRAPHICS->GetCB(CB_TYPE::MATERIAL);
	pCB->SetData(&m_tMtrlConst);
	pCB->UpdateData();
}

void CMaterial::SetTexParam(TEX_PARAM _eParam, Ptr<CTexture> _pTex)
{
	//	enum class TEX_PARAM : 
	//		TEX_0, TEX_1, TEX_2, TEX_3, TEX_4, TEX_5,
	//		TEXCUBE_0, TEXCUBE_1,
	//		TEXARR_0, TEXARR_1,

	m_arrTex[(int32)_eParam] = _pTex;
}
