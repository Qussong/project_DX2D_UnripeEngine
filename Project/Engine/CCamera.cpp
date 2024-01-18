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

void CCamera::ViewMatrix()
{
	// 카메라 컴포넌트를 소유한 GameObject 객체의 로컬상에서의 위치값
	Vec3 v3CamPos = GetOwner()->Transform()->GetRelativePos();

	// View 변환에서 "위치변환"은 카메라가 이동한만큼 반대로 돌아가면된다.
	// 때문에 카메라 위치 좌표에 -1 을 곱해준 거리만큼 이동변환 해주면 된다.
	Matrix matRevTrans = XMMatrixTranslation(-v3CamPos.x, -v3CamPos.y, -v3CamPos.z);

	// 카메라 컴포넌트를 소유한 GameObject 객체의 로컬상에서의 회전값
	Vec3 v3RotX = GetOwner()->Transform()->GetDirection(DIR_TYPE::RIGHT);
	Vec3 v3RotY = GetOwner()->Transform()->GetDirection(DIR_TYPE::UP);
	Vec3 v3RotZ = GetOwner()->Transform()->GetDirection(DIR_TYPE::FRONT);

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

	// 상수버퍼 대응 구조체 값 세팅
	g_tTransform.matView = m_matView;
}

void CCamera::ProjectionMatrix()
{
	g_tTransform.matProj = m_matProj;
}

void CCamera::FinalTick()
{
	ViewMatrix();
	ProjectionMatrix();
}
