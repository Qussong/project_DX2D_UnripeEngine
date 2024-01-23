#include "pch.h"
#include "CTransform.h"

CTransform::CTransform()
	: Super(COMPONENT_TYPE::TRANSFORM)
	, m_v3LocalPostion(Vec3(0.f, 0.f, 0.f))
	, m_v3LocalScale(Vec3(1.0f, 1.0f, 1.0f))
	, m_v3LocalRotation(Vec3(0.f, 0.f, 0.f))
	, m_arrLocalDir{}
	, m_matWorld {}
	, m_isAffectScale(false)
{
	SetName(L"Transform");
}

CTransform::~CTransform()
{
}

void CTransform::FinalTick()
{
	// S,R,T 타입 변환 (Vec3 -> Matrix)
	Matrix matScale = XMMatrixScaling(m_v3LocalScale.x, m_v3LocalScale.y, m_v3LocalScale.z);
	Matrix matRotX = XMMatrixRotationX(m_v3LocalRotation.x);
	Matrix matRotY = XMMatrixRotationY(m_v3LocalRotation.y);
	Matrix matRotZ = XMMatrixRotationZ(m_v3LocalRotation.z);
	Matrix matTrans = XMMatrixTranslation(m_v3LocalPostion.x, m_v3LocalPostion.y, m_v3LocalPostion.z);

	// World 행렬
	m_matWorld = XMMatrixIdentity();
	m_matWorld = m_matWorld * matScale * (matRotX * matRotY * matRotZ) * matTrans;

	// 기저벡터
	Vec3 arrDefaultDir[(UINT)DIR_TYPE::END] = {};
	arrDefaultDir[(UINT)DIR_TYPE::RIGHT]	= Vec3(1.f, 0.f, 0.f);
	arrDefaultDir[(UINT)DIR_TYPE::UP]		= Vec3(0.f, 1.f, 0.f);
	arrDefaultDir[(UINT)DIR_TYPE::FRONT]	= Vec3(0.f, 0.f, 1.f);

	// 각 축에 대한 기저 벡터에 월드 행렬을 곱한다.
	// 결과 값을 Normalize 함으로써 현재 바라보고 있는 방향 벡터를 구한다.
	for (size_t i = 0; i < (UINT)DIR_TYPE::END; ++i)
	{
		m_arrLocalDir[i] = XMVector3TransformNormal(arrDefaultDir[i], m_matWorld);
		m_arrLocalDir[i].Normalize();

		// 부모객체가 없는 경우 LocalDir == WorldDir
		m_arrWorldDir[i] = m_arrLocalDir[i];
	}

	CGameObject* pParent = GetOwner()->GetParent();
	// 부모 객체가 존재하는 경우
	if (nullptr != pParent)
	{
		// 부모 객체의 TransformComp
		CTransform* pParentTransComp = pParent->Transform();
		// 부모 객체의 World 변환 행렬(SRT)
		const Matrix& matParentSRT = pParentTransComp->GetWorldMatrix();

		// WorldMatrix
		// 부모 객체로부터 Scale 영향을 받을경우
		if (m_isAffectScale)
		{
			m_matWorld *= matParentSRT;
		}
		// 부모 객체로부터 Scale 영향을 받지 않을경우
		else
		{
			Vec3 v3ParentScale = pParentTransComp->GetLocalScale();
			Vec3 v3ParentScaleInv = Vec3(1.f / v3ParentScale.x, 1.f / v3ParentScale.y, 1.f / v3ParentScale.z);
			Matrix matParnetScaleInv = XMMatrixScaling(v3ParentScaleInv.x, v3ParentScaleInv.y, v3ParentScaleInv.z);

			Matrix matParentRT = matParnetScaleInv * matParentSRT;
			m_matWorld *= matParentRT;
		}

		// Direction
		for (size_t i = 0; i < (UINT)DIR_TYPE::END; ++i)
		{
			m_arrWorldDir[i] = XMVector3TransformNormal(arrDefaultDir[i], m_matWorld);
			m_arrWorldDir[i].Normalize();
		}
	}
}

void CTransform::UpdateData()
{
	g_tTransform.matWorld = m_matWorld;

	// 0번 Register 에 바인딩
	CConstantBuffer* pCB = GRAPHICS->GetCB(CB_TYPE::TRANSFORM);
	pCB->SetData(&g_tTransform);
	pCB->UpdateData(static_cast<uint32>(CB_TYPE::TRANSFORM));
}