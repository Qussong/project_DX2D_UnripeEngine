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

void CTransform::Begin()
{
}

void CTransform::Tick()
{
}

void CTransform::FinalTick()
{
}

void CTransform::UpdateData()
{
	tTransform transform = {};
	transform.v4WorldPos = Vec4(m_v3RelativePostion, 0.f);
	transform.v4WorldScale = Vec4(m_v3RelativeScale, 0.f);


	uint32 registerNum = 0;
	CConstantBuffer* pCB = GRAPHICS->GetConstantBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&transform);
	pCB->UpdateData(registerNum);
}