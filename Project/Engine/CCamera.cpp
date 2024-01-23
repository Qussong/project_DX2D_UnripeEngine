#include "pch.h"
#include "CCamera.h"

CCamera::CCamera()
	: Super(COMPONENT_TYPE::CAMERA)
	, m_eProjType(PROJ_TYPE::ORTHOGRAPHIC)
	, m_fFOV(XM_PI / 2.f)	// 90º
	, m_fScale(1.f)
	, m_v2Resolution(Vec2(0.f, 0.f))
	, m_fAspectRatio(1.f)
	, m_fNear(1.f)
	, m_fFar(1000.f)
{
	m_matView = XMMatrixIdentity();
	m_matProj = XMMatrixIdentity();
	m_v2Resolution = GRAPHICS->GetResolution();
	m_fAspectRatio = m_v2Resolution.x / m_v2Resolution.y;
}

CCamera::~CCamera()
{
}

void CCamera::ViewMatrix()
{
	// 카메라 컴포넌트를 소유한 GameObject 객체의 로컬상에서의 위치값
	Vec3 v3CamPos = GetOwner()->Transform()->GetLocalPos();

	// View 변환에서 "위치변환"은 카메라가 이동한만큼 반대로 돌아가면된다.
	// 때문에 카메라 위치 좌표에 -1 을 곱해준 거리만큼 이동변환 해주면 된다.
	Matrix matRevTrans = XMMatrixTranslation(-v3CamPos.x, -v3CamPos.y, -v3CamPos.z);

	// 카메라 컴포넌트를 소유한 GameObject 객체의 로컬상에서의 회전값
	Vec3 v3RotX = GetOwner()->Transform()->GetLocalDirection(DIR_TYPE::RIGHT);
	Vec3 v3RotY = GetOwner()->Transform()->GetLocalDirection(DIR_TYPE::UP);
	Vec3 v3RotZ = GetOwner()->Transform()->GetLocalDirection(DIR_TYPE::FRONT);

	// View 변환에 "회전변환"은 카메라가 화전한만큼 반대로 돌아가면된다.
	// 때문에 카메라의 회전변환행렬의 역행렬을 구해서 곱해주면된다.
	// 회전변환 행렬의 전치행렬 == 역행렬
	//////////////////////////////////////////////////////////////////////////
	// 회전변환에서 전치행렬 == 역행렬 성질 정리할 것
	//////////////////////////////////////////////////////////////////////////
	Matrix matRevRot = XMMatrixIdentity();
	matRevRot._11 = v3RotX.x; matRevRot._12 = v3RotY.x; matRevRot._13 = v3RotZ.x;
	matRevRot._21 = v3RotX.y; matRevRot._22 = v3RotY.y; matRevRot._23 = v3RotZ.y;
	matRevRot._31 = v3RotX.z; matRevRot._32 = v3RotY.z; matRevRot._33 = v3RotZ.z;

	// View 행렬 완성 (위치변환, 회전변환 적용)
	// 역행렬을 곱해주는것이기에 곱해준 순서의 반대 순서로 연산해준다.
	// 순방향 : SRT -> 역방향 : TRS
	m_matView = matRevTrans * matRevRot;
}

void CCamera::ProjectionMatrix()
{
	// 직교투영 (Orthographic)
	if (PROJ_TYPE::ORTHOGRAPHIC == m_eProjType)
	{
		float fViewWidth = m_v2Resolution.x * m_fScale;
		float fViewHeight = m_v2Resolution.y * m_fScale;
		m_matProj = XMMatrixOrthographicLH(fViewWidth, fViewHeight, m_fNear, m_fFar);
	}
	// 원근투영 (Perspective)
	if (PROJ_TYPE::PERSPECTIVE == m_eProjType)
	{
		m_matProj = XMMatrixPerspectiveFovLH(m_fFOV, m_fAspectRatio, m_fNear, m_fFar);
	}
}

void CCamera::FinalTick()
{
	ViewMatrix();
	ProjectionMatrix();

	// 상수버퍼 대응 구조체 값 세팅
	g_tTransform.matView = m_matView;
	g_tTransform.matProj = m_matProj;
}