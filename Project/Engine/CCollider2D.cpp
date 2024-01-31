#include "pch.h"
#include "CCollider2D.h"

CCollider2D::CCollider2D()
	: Super(COMPONENT_TYPE::COLLIDER2D)
	, m_v3OffsetPos{}
	, m_v3OffsetScale{}
	, m_iCollisionCnt(0)
	, m_bAbsolute(false)
	, m_eType(COLLIDER2D_TYPE::RECT)
{
}

CCollider2D::~CCollider2D()
{
}

void CCollider2D::FinalTick()
{
	// �浹ü�� ���� ��� ���
	Matrix matLocalScale = XMMatrixScaling(m_v3OffsetScale.x, m_v3OffsetScale.y, m_v3OffsetScale.z);
	Matrix matLocalPos = XMMatrixTranslation(m_v3OffsetPos.x, m_v3OffsetPos.y, m_v3OffsetPos.z);
	m_matColWorld = matLocalScale * matLocalPos;

	// �浹ü�� �����ų ������(GameObject)�� �������
	const Matrix& matOwnerWorld = GetOwner()->Transform()->GetWorldMatrix();

	// �������� Scale�� ������ ���� �������� ���
	if (m_bAbsolute)
	{
		Vec3 v3WorldScale = GetOwner()->Transform()->GetWorldScale();
		Matrix matScale = XMMatrixScaling(v3WorldScale.x, v3WorldScale.y, v3WorldScale.z);
		Matrix matScaleInv = XMMatrixInverse(nullptr, matScale);

		// Owner�� Scale�� ������� ���̿� ��ġ�Ͽ� Scale�� ������ ����Ŵ
		m_matColWorld = m_matColWorld * matScaleInv * matOwnerWorld;
	}
	// �������� Scale�� ������ �������� ���
	else
	{
		m_matColWorld *= matOwnerWorld;
	}

	// �浹���̸� Red
	if (0 == m_iCollisionCnt)
	{
		GamePlayStatic::DrawDebugRect(m_matColWorld, Vec3(0.f, 1.f, 0.f));
	}
	// �浹�ϰ� ���� ������ Green
	else
	{
		GamePlayStatic::DrawDebugRect(m_matColWorld, Vec3(1.f, 0.f, 0.f));
	}
}
