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
	// 충돌체의 월드 행렬 계산
	Matrix matLocalScale = XMMatrixScaling(m_v3OffsetScale.x, m_v3OffsetScale.y, m_v3OffsetScale.z);
	Matrix matLocalPos = XMMatrixTranslation(m_v3OffsetPos.x, m_v3OffsetPos.y, m_v3OffsetPos.z);
	m_matColWorld = matLocalScale * matLocalPos;

	// 충돌체에 적용시킬 소유자(GameObject)의 월드행렬
	const Matrix& matOwnerWorld = GetOwner()->Transform()->GetWorldMatrix();

	// 소유자의 Scale에 영향을 받지 않으려는 경우
	if (m_bAbsolute)
	{
		Vec3 v3WorldScale = GetOwner()->Transform()->GetWorldScale();
		Matrix matScale = XMMatrixScaling(v3WorldScale.x, v3WorldScale.y, v3WorldScale.z);
		Matrix matScaleInv = XMMatrixInverse(nullptr, matScale);

		// Owner의 Scale의 역행렬을 사이에 배치하여 Scale의 영향을 상쇄시킴
		m_matColWorld = m_matColWorld * matScaleInv * matOwnerWorld;
	}
	// 소유자의 Scale에 영향을 받으려는 경우
	else
	{
		m_matColWorld *= matOwnerWorld;
	}

	// 충돌중이면 Red
	if (0 == m_iCollisionCnt)
	{
		GamePlayStatic::DrawDebugRect(m_matColWorld, Vec3(0.f, 1.f, 0.f));
	}
	// 충돌하고 있지 않으면 Green
	else
	{
		GamePlayStatic::DrawDebugRect(m_matColWorld, Vec3(1.f, 0.f, 0.f));
	}
}
