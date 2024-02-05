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
	// �ش� �������� ���� ��ġ�� tLightInfo.v3WorldPos�� ����
	Vec3 v3WorldPos = GetOwner()->Transform()->GetWorldPos();
	m_tLightInfo.v3WorldPos = v3WorldPos;

	// ���� ���
	M_RENDER->RegisterLight2D(this);
}