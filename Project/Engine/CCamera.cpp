#include "pch.h"
#include "CCamera.h"

CCamera::CCamera()
	: Super(COMPONENT_TYPE::CAMERA)
	, m_eProjType(PROJ_TYPE::ORTHOGRAPHIC)
	, m_fFOV(XM_PI / 2.f)	// 90��
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
	// ī�޶� ������Ʈ�� ������ GameObject ��ü�� ���û󿡼��� ��ġ��
	Vec3 v3CamPos = GetOwner()->Transform()->GetLocalPos();

	// View ��ȯ���� "��ġ��ȯ"�� ī�޶� �̵��Ѹ�ŭ �ݴ�� ���ư���ȴ�.
	// ������ ī�޶� ��ġ ��ǥ�� -1 �� ������ �Ÿ���ŭ �̵���ȯ ���ָ� �ȴ�.
	Matrix matRevTrans = XMMatrixTranslation(-v3CamPos.x, -v3CamPos.y, -v3CamPos.z);

	// ī�޶� ������Ʈ�� ������ GameObject ��ü�� ���û󿡼��� ȸ����
	Vec3 v3RotX = GetOwner()->Transform()->GetLocalDirection(DIR_TYPE::RIGHT);
	Vec3 v3RotY = GetOwner()->Transform()->GetLocalDirection(DIR_TYPE::UP);
	Vec3 v3RotZ = GetOwner()->Transform()->GetLocalDirection(DIR_TYPE::FRONT);

	// View ��ȯ�� "ȸ����ȯ"�� ī�޶� ȭ���Ѹ�ŭ �ݴ�� ���ư���ȴ�.
	// ������ ī�޶��� ȸ����ȯ����� ������� ���ؼ� �����ָ�ȴ�.
	// ȸ����ȯ ����� ��ġ��� == �����
	//////////////////////////////////////////////////////////////////////////
	// ȸ����ȯ���� ��ġ��� == ����� ���� ������ ��
	//////////////////////////////////////////////////////////////////////////
	Matrix matRevRot = XMMatrixIdentity();
	matRevRot._11 = v3RotX.x; matRevRot._12 = v3RotY.x; matRevRot._13 = v3RotZ.x;
	matRevRot._21 = v3RotX.y; matRevRot._22 = v3RotY.y; matRevRot._23 = v3RotZ.y;
	matRevRot._31 = v3RotX.z; matRevRot._32 = v3RotY.z; matRevRot._33 = v3RotZ.z;

	// View ��� �ϼ� (��ġ��ȯ, ȸ����ȯ ����)
	// ������� �����ִ°��̱⿡ ������ ������ �ݴ� ������ �������ش�.
	// ������ : SRT -> ������ : TRS
	m_matView = matRevTrans * matRevRot;
}

void CCamera::ProjectionMatrix()
{
	// �������� (Orthographic)
	if (PROJ_TYPE::ORTHOGRAPHIC == m_eProjType)
	{
		float fViewWidth = m_v2Resolution.x * m_fScale;
		float fViewHeight = m_v2Resolution.y * m_fScale;
		m_matProj = XMMatrixOrthographicLH(fViewWidth, fViewHeight, m_fNear, m_fFar);
	}
	// �������� (Perspective)
	if (PROJ_TYPE::PERSPECTIVE == m_eProjType)
	{
		m_matProj = XMMatrixPerspectiveFovLH(m_fFOV, m_fAspectRatio, m_fNear, m_fFar);
	}
}

void CCamera::FinalTick()
{
	ViewMatrix();
	ProjectionMatrix();

	// ������� ���� ����ü �� ����
	g_tTransform.matView = m_matView;
	g_tTransform.matProj = m_matProj;
}