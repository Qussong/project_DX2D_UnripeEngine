#include "pch.h"
#include "CLight2D.h"

CLight2D::CLight2D()
	: Super(COMPONENT_TYPE::LIGHT2D)
{
	SetName(L"Light2D");
}

CLight2D::~CLight2D()
{
}

void CLight2D::FinalTick()
{
	// 해당 프레임의 월드 위치를 tLightInfo.v3WorldPos에 갱신
	Vec3 v3WorldPos = GetOwner()->Transform()->GetWorldPos();
	m_tLightInfo.v3WorldPos = v3WorldPos;

	// 광원 등록
	M_RENDER->RegisterLight2D(this);
}