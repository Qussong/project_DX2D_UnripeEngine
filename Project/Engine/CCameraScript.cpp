#include "pch.h"
#include "CCameraScript.h"

CCameraScript::CCameraScript()
	: m_fCamSpeed(100.f)
	, m_fDragSpeed(10.f * 180.f)
{
}

CCameraScript::~CCameraScript()
{
}

void CCameraScript::Tick()
{
	// 카메라 투영 타입
	PROJ_TYPE projType = GetOwner()->Camera()->GetProjectionType();
	// 카메라 컴포넌트를 소유한 GameObjectdml 로컬상의 위치값
	Vec3 v3Pos = GetOwner()->Transform()->GetRelativePos();
	// 카메라 컴포넌트를 소유한 GameObjectdml 로컬상의 회전값
	Vec3 v3Rot = GetOwner()->Transform()->GetRelativeRotation();
	// 마우스 드래그 방향
	Vec2 v2DragDir = CKeyMgr::GetInst()->GetMouseDragDir();

	// 카메라 투영 방식 변경 (직교투영 ↔ 원근투영)
	if (KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(KEY::P))
	{
		if (PROJ_TYPE::ORTHOGRAPHIC == projType)
		{
			GetOwner()->Camera()->SetProjectionType(PROJ_TYPE::PERSPECTIVE);
		}
		else
		{
			GetOwner()->Camera()->SetProjectionType(PROJ_TYPE::ORTHOGRAPHIC);
			GetOwner()->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		}
	}

	// 위치이동 (상,하,좌,우)
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::W))
	{
		if(PROJ_TYPE::ORTHOGRAPHIC == projType)
			v3Pos.y += m_fCamSpeed * DT;
		if(PROJ_TYPE::PERSPECTIVE == projType)
			v3Pos.z += m_fCamSpeed * DT;
	}
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::S))
	{
		if (PROJ_TYPE::ORTHOGRAPHIC == projType)
			v3Pos.y -= m_fCamSpeed * DT;
		if (PROJ_TYPE::PERSPECTIVE == projType)
			v3Pos.z -= m_fCamSpeed * DT;
	}
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::A))
	{
		v3Pos.x -= m_fCamSpeed * DT;
	}
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::D))
	{
		v3Pos.x += m_fCamSpeed * DT;
	}

	// 회전이동 (조건 : 원근투영)
	if (PROJ_TYPE::PERSPECTIVE == projType)
	{
		if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::RBTN))
		{
			// 회전이동시 드래그 값의 변화값에서 
			// x의 변화량을 y에, y의 변화량을 x에 적용시키는 이유 : 
			// x축 방향으로 드래그하면 y축 기준으로 회전해야하고,
			// y축 방향으로 드래그하면 x축이 회전해야한다.
			v3Rot.x += (v2DragDir.y * (XM_PI / 180) * m_fDragSpeed * DT);
			v3Rot.y += (v2DragDir.x * (XM_PI / 180) * m_fDragSpeed * DT);
		}
	}

	// 확대, 축소



	GetOwner()->Transform()->SetRelativePos(v3Pos);
	GetOwner()->Transform()->SetRelativeRotation(v3Rot);
}
