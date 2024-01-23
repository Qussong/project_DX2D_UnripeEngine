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
	// S,R,T Ÿ�� ��ȯ (Vec3 -> Matrix)
	Matrix matScale = XMMatrixScaling(m_v3LocalScale.x, m_v3LocalScale.y, m_v3LocalScale.z);
	Matrix matRotX = XMMatrixRotationX(m_v3LocalRotation.x);
	Matrix matRotY = XMMatrixRotationY(m_v3LocalRotation.y);
	Matrix matRotZ = XMMatrixRotationZ(m_v3LocalRotation.z);
	Matrix matTrans = XMMatrixTranslation(m_v3LocalPostion.x, m_v3LocalPostion.y, m_v3LocalPostion.z);

	// World ���
	m_matWorld = XMMatrixIdentity();
	m_matWorld = m_matWorld * matScale * (matRotX * matRotY * matRotZ) * matTrans;

	// ��������
	Vec3 arrDefaultDir[(UINT)DIR_TYPE::END] = {};
	arrDefaultDir[(UINT)DIR_TYPE::RIGHT]	= Vec3(1.f, 0.f, 0.f);
	arrDefaultDir[(UINT)DIR_TYPE::UP]		= Vec3(0.f, 1.f, 0.f);
	arrDefaultDir[(UINT)DIR_TYPE::FRONT]	= Vec3(0.f, 0.f, 1.f);

	// �� �࿡ ���� ���� ���Ϳ� ���� ����� ���Ѵ�.
	// ��� ���� Normalize �����ν� ���� �ٶ󺸰� �ִ� ���� ���͸� ���Ѵ�.
	for (size_t i = 0; i < (UINT)DIR_TYPE::END; ++i)
	{
		m_arrLocalDir[i] = XMVector3TransformNormal(arrDefaultDir[i], m_matWorld);
		m_arrLocalDir[i].Normalize();

		// �θ�ü�� ���� ��� LocalDir == WorldDir
		m_arrWorldDir[i] = m_arrLocalDir[i];
	}

	CGameObject* pParent = GetOwner()->GetParent();
	// �θ� ��ü�� �����ϴ� ���
	if (nullptr != pParent)
	{
		// �θ� ��ü�� TransformComp
		CTransform* pParentTransComp = pParent->Transform();
		// �θ� ��ü�� World ��ȯ ���(SRT)
		const Matrix& matParentSRT = pParentTransComp->GetWorldMatrix();

		// WorldMatrix
		// �θ� ��ü�κ��� Scale ������ �������
		if (m_isAffectScale)
		{
			m_matWorld *= matParentSRT;
		}
		// �θ� ��ü�κ��� Scale ������ ���� �������
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

	// 0�� Register �� ���ε�
	CConstantBuffer* pCB = GRAPHICS->GetCB(CB_TYPE::TRANSFORM);
	pCB->SetData(&g_tTransform);
	pCB->UpdateData(static_cast<uint32>(CB_TYPE::TRANSFORM));
}