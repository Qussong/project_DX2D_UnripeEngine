#include "pch.h"
#include "CTransform.h"

CTransform::CTransform()
	: Super(COMPONENT_TYPE::TRANSFORM)
	, m_v3RelativePostion(Vec3(0.f, 0.f, 0.f))
	, m_v3RelativeScale(Vec3(1.0f, 1.0f, 1.0f))
	, m_v3RelativeRotation(Vec3(0.f, 0.f, 0.f))
	, m_arrDir{}
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
	Matrix matTrans = XMMatrixTranslation(m_v3RelativePostion.x, m_v3RelativePostion.y, m_v3RelativePostion.z);

	// World 행렬
	m_matWorld = XMMatrixIdentity();
	m_matWorld = m_matWorld * matScale * (matRotX * matRotY * matRotZ) * matTrans;

	// 방향벡터
	m_arrDir[(UINT)DIR_TYPE::RIGHT]	= Vec3(1.f, 0.f, 0.f);
	m_arrDir[(UINT)DIR_TYPE::UP]	= Vec3(0.f, 1.f, 0.f);
	m_arrDir[(UINT)DIR_TYPE::FRONT]	= Vec3(0.f, 0.f, 1.f);
	// 각 축에 대한 기저 벡터에 월드 행렬을 곱한다.
	// 결과 값을 Normalize 함으로써 현재 바라보고 있는 방향 벡터를 구한다.
	for (size_t i = 0; i < (UINT)DIR_TYPE::END; ++i)
	{
		m_arrDir[i] = XMVector3TransformNormal(m_arrDir[i], m_matWorld);
		m_arrDir[i].Normalize();
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