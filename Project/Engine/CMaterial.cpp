#include "pch.h"
#include "CMaterial.h"

CMaterial::CMaterial()
	: Super(ASSET_TYPE::MATERIAL)
	, m_tConst{}
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
	if (nullptr != m_pShader)
		m_pShader->UpdateData();

	CConstantBuffer* pCB = GRAPHICS->GetCB(CB_TYPE::MATERIAL);
	pCB->SetData(&m_tConst);
	pCB->UpdateData();
}