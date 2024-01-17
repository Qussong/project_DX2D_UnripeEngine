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
	Vec3 v3Scale = transform->GetRelativeScale();
	Vec3 v3Rot = transform->GetRelativeRotation();
	Vec3 v3Pos = transform->GetRelativePos();

	bool posFlag = false;
	bool rotFlag = false;

	// Position
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::LEFT))
	{
		v3Pos.x -= m_fSpeed * DT;
		posFlag = true;
	}
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT))
	{
		v3Pos.x += m_fSpeed * DT;
		posFlag = true;
	}
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::UP))
	{
		v3Pos.y += m_fSpeed * DT;
		posFlag = true;
	}
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::DOWN))
	{
		v3Pos.y -= m_fSpeed * DT;
		posFlag = true;
	}


	// Rotation
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::LCTRL))
	{
		if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::X))
		{
			v3Rot.x -= DT * XM_PI;
			rotFlag = true;
		}
		if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::Y))
		{
			v3Rot.y -= DT * XM_PI;
			rotFlag = true;
		}
		if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::Z))
		{
			v3Rot.z -= DT * XM_PI;
			rotFlag = true;
		}
	}
	else
	{
		if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::X))
		{
			v3Rot.x += DT * XM_PI;
			rotFlag = true;
		}
		if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::Y))
		{
			v3Rot.y += DT * XM_PI;
			rotFlag = true;
		}
		if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::Z))
		{
			v3Rot.z += DT * XM_PI;
			rotFlag = true;
		}
	}

	// monitoring
	if (posFlag)
	{
		cout << "X " << (int)(v3Pos[0] * GRAPHICS->GetResolution().x / 2)
			<< "/Y " << (int)(v3Pos[1] * GRAPHICS->GetResolution().y / 2) << endl;
	}
	if (rotFlag)
	{
		cout << "X " << (int)(v3Rot[0] * 180) << "им"
			<< "/Y " << (int)(v3Rot[1] * 180) << "им"
			<< "/Z " << (int)(v3Rot[2] * 180) << "им" << endl;
	}

	transform->SetRelativePos(v3Pos);
	transform->SetRelativeRotation(v3Rot);
}