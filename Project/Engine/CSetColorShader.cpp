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

void CSetColorShader::UpdateData()
{
	m_tMtrlConst.v4Arr[0] = m_v4Color;
}

void CSetColorShader::Clear()
{
}
