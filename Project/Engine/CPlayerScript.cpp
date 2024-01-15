#include "pch.h"
#include "CPlayerScript.h"

CPlayerScript::CPlayerScript()
	: m_fSpeed(1.f)
{
	SetName(L"PlayerScript");
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Tick()
{
	CGameObject* owner = GetOwner();
	CTransform* transform = owner->Transform();
	Vec3 pos = transform->GetRelativePos();

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::LEFT))
	{
		pos.x -= m_fSpeed * DT;

		cout << "X " << (int)(pos[0] * 255)
			<< "/Y " << (int)(pos[1] * 255) << endl;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT))
	{
		pos.x += m_fSpeed * DT;

		cout << "X " << (int)(pos[0] * 255)
			<< "/Y " << (int)(pos[1] * 255) << endl;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::UP))
	{
		pos.y += m_fSpeed * DT;

		cout << "X " << (int)(pos[0] * 255)
			<< "/Y " << (int)(pos[1] * 255) << endl;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::DOWN))
	{
		pos.y -= m_fSpeed * DT;

		cout << "X " << (int)(pos[0] * 255)
			<< "/Y " << (int)(pos[1] * 255) << endl;
	}

	transform->SetRelativePos(pos);
}
