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
	// key test
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::LEFT))
	{
		m_v3RelativePostion.x -= DT;

		cout << "X " << (int)(m_v3RelativePostion[0] * 255)
			<< "/Y " << (int)(m_v3RelativePostion[1] * 255) << endl;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT))
	{
		m_v3RelativePostion.x += DT;

		cout << "X " << (int)(m_v3RelativePostion[0] * 255)
			<< "/Y " << (int)(m_v3RelativePostion[1] * 255) << endl;
	}

	tTransform transform = {};
	transform.v4WorldPos = Vec4(m_v3RelativePostion, 0.f);
	transform.v4WorldScale = Vec4(m_v3RelativeScale, 0.f);


	uint32 registerNum = 0;
	CConstantBuffer* pCB = GRAPHICS->GetConstantBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&transform);
	pCB->UpdateData(registerNum);
}