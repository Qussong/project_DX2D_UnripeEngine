#include "pch.h"
#include "CTransform.h"

CTransform::CTransform()
	: Super(COMPONENT_TYPE::TRANSFORM)
	, m_v3RelativePostion(Vec3(0.f, 0.f, 0.f))
	, m_v3RelativeScale(Vec3(1.0f, 1.0f, 1.0f))
	, m_v3RelativeRotation(Vec3(0.f, 0.f, 0.f))
	, m_arrDirection {}
	, m_matWorld {}
{
	SetName(L"Transform");
}

CTransform::~CTransform()
{
}

void CTransform::FinalTick()
{
	// S,R,T 의 단위 : Vec3 -> Matrix
	Matrix matScale = XMMatrixScaling(m_v3RelativeScale.x, m_v3RelativeScale.y, m_v3RelativeScale.z);
	Matrix matRotX = XMMatrixRotationX(m_v3RelativeRotation.x);
	Matrix matRotY = XMMatrixRotationY(m_v3RelativeRotation.y);
	Matrix matRotZ = XMMatrixRotationZ(m_v3RelativeRotation.z);
	Matrix matTranslation = XMMatrixTranslation(m_v3RelativePostion.x, m_v3RelativePostion.y, m_v3RelativePostion.z);

	// World 행렬
	m_matWorld = XMMatrixIdentity();
	m_matWorld = m_matWorld * matScale * (matRotX * matRotY * matRotZ) * matTranslation;

	// 방향벡터
	m_arrDirection[(UINT)DIR_TYPE::UP] = Vec3(1.f, 0.f, 0.f);
	m_arrDirection[(UINT)DIR_TYPE::FRONT] = Vec3(0.f, 1.f, 0.f);
	m_arrDirection[(UINT)DIR_TYPE::RIGHT] = Vec3(0.f, 0.f, 1.f);
	for (size_t i = 0; i < (UINT)DIR_TYPE::END; ++i)
	{
		m_arrDirection[i] = XMVector3TransformNormal(m_arrDirection[i], m_matWorld);
		m_arrDirection[i].Normalize();
	}
}

void CTransform::UpdateData()
{
	tTransform transform = {};
	transform.matWorld = m_matWorld;

	// 0번 Register 에 바인딩
	uint32 registerNum = 0;
	CConstantBuffer* pCB = GRAPHICS->GetConstantBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&transform);
	pCB->UpdateData(registerNum);
}