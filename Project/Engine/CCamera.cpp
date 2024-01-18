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
	// ī�޶� ������Ʈ�� ������ GameObject ��ü�� ���û󿡼��� ��ġ��
	Vec3 v3CamPos = GetOwner()->Transform()->GetRelativePos();

	// View ��ȯ���� "��ġ��ȯ"�� ī�޶� �̵��Ѹ�ŭ �ݴ�� ���ư���ȴ�.
	// ������ ī�޶� ��ġ ��ǥ�� -1 �� ������ �Ÿ���ŭ �̵���ȯ ���ָ� �ȴ�.
	Matrix matRevTrans = XMMatrixTranslation(-v3CamPos.x, -v3CamPos.y, -v3CamPos.z);

	// ī�޶� ������Ʈ�� ������ GameObject ��ü�� ���û󿡼��� ȸ����
	Vec3 v3RotX = GetOwner()->Transform()->GetDirection(DIR_TYPE::RIGHT);
	Vec3 v3RotY = GetOwner()->Transform()->GetDirection(DIR_TYPE::UP);
	Vec3 v3RotZ = GetOwner()->Transform()->GetDirection(DIR_TYPE::FRONT);

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

	// ������� ���� ����ü �� ����
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
