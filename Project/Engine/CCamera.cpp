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

	// View 변환은 카메라가 이동한 값을 그대로 되돌아가면된다.
	// 때문에 카메라 위치 좌표에 -1 을 곱해주면 View 변환이 된다.
	m_matView._41 = (-1) * vCamPos.x;
	m_matView._42 = (-1) * vCamPos.y;
	m_matView._43 = (-1) * vCamPos.z;

	// 상수버퍼 대응 구조체 값 세팅
	g_tTransform.matView = m_matView;
	g_tTransform.matProj = m_matProj;
}
