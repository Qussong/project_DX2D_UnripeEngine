#include "pch.h"
#include "CCameraScript.h"

CCameraScript::CCameraScript()
	: m_fCamSpeed(1.f)
	, m_fDragSpeed(10.f * 180.f)
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
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::RBTN))
	{
		Vec3 v3Rot = GetOwner()->Transform()->GetRelativeRotation();
		Vec2 v2DragDir = CKeyMgr::GetInst()->GetMouseDragDir();
		//////////////////////////////////////////////////////////////////////////
		// 회전이동시 드래그 값의 변화값에서 
		// x의 변화량을 y에, y의 변화량을 x에 적용시키는 이유 : 
		// x축 드래그하면 y축으로 회전하고, y축으로 드래그하면 x축으로 회전한다.
		//////////////////////////////////////////////////////////////////////////
		v3Rot.x += (v2DragDir.y * (XM_PI / 180) * m_fDragSpeed * DT);
		v3Rot.y += (v2DragDir.x * (XM_PI / 180) * m_fDragSpeed * DT);

		GetOwner()->Transform()->SetRelativeRotation(v3Rot);
	}

	// FOV (확대, 축소)

}
