#include "pch.h"
#include "CCameraScript.h"

CCameraScript::CCameraScript()
	: m_fCamSpeed(1.f)
{
}

CCameraScript::~CCameraScript()
{
}

void CCameraScript::Tick()
{
	// 카메라 컴포넌트를 소유한 GameObjectdml 로컬상의 위치값
	Vec3 v3Pos = GetOwner()->Transform()->GetRelativePos();

	// 위치이동 (상,하,좌,우)
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::W))
	{
		v3Pos.y += m_fCamSpeed * DT;
	}
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::S))
	{
		v3Pos.y -= m_fCamSpeed * DT;
	}
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::A))
	{
		v3Pos.x -= m_fCamSpeed * DT;
	}
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::D))
	{
		v3Pos.x += m_fCamSpeed * DT;
	}
	GetOwner()->Transform()->SetRelativePos(v3Pos);

	// 회전이동

	// FOV (확대, 축소)
}
