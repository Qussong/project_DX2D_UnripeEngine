#include "pch.h"
#include "CSetColorShader.h"

CSetColorShader::CSetColorShader()
	: Super(32, 32, 1)
	, m_v4Color{}
{
}

CSetColorShader::~CSetColorShader()
{
}

int CSetColorShader::UpdateData()
{
	if (nullptr == m_pTargetTex)
		return E_FAIL;

	// 상수버퍼 값 설정
	m_tMtrlConst.iArr[0] = m_pTargetTex->GetWidth();
	m_tMtrlConst.iArr[1] = m_pTargetTex->GetHeight();
	m_tMtrlConst.v4Arr[0] = m_v4Color;

	// Texture u0 레지스터에 바인딩
	if (FAILED(m_pTargetTex->UpdateData_CS_UAV(0)))
		return E_FAIL;

	// Thread 그룹 수 체크
	UINT iWidth = m_pTargetTex->GetWidth();
	UINT iHeight = m_pTargetTex->GetHeight();

	SetGroupX(1 + iWidth / m_iThreadX);
	SetGroupY(1 + iHeight / m_iThreadY);
	SetGroupZ(1);

	return S_OK;
}

void CSetColorShader::Clear()
{
	m_pTargetTex->Clear_CS_UAV();
}