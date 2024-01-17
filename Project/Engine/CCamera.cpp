#include "pch.h"
#include "CCamera.h"

CCamera::CCamera()
	: Super(COMPONENT_TYPE::CAMERA)
	, m_fFOV(0.f)
	, m_fWidth(0.f)
	, m_fHeight(0.f)
	, m_fAspectRatio(0.f)
	, m_fFar(1000.f)
	, m_matView(XMMatrixIdentity())
	, m_matProj(XMMatrixIdentity())
{
}

CCamera::~CCamera()
{
}

void CCamera::FinalTick()
{
	Vec3 vCamPos = GetOwner()->Transform()->GetRelativePos();

	// View ��ȯ�� ī�޶� �̵��� ���� �״�� �ǵ��ư���ȴ�.
	// ������ ī�޶� ��ġ ��ǥ�� -1 �� �����ָ� View ��ȯ�� �ȴ�.
	m_matView._41 = (-1) * vCamPos.x;
	m_matView._42 = (-1) * vCamPos.y;
	m_matView._43 = (-1) * vCamPos.z;

	// ������� ���� ����ü �� ����
	g_tTransform.matView = m_matView;
	g_tTransform.matProj = m_matProj;
}
