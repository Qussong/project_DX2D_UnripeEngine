#include "pch.h"
#include "CCameraScript.h"

CCameraScript::CCameraScript()
	: m_fCamSpeed(100.f)
	, m_fDragSpeed(2.5f * 180.f)
	, m_fWheelSpeed(25.f)
{
}

CCameraScript::~CCameraScript()
{
}

void CCameraScript::Tick()
{
	// 카메라 투영 타입
	PROJ_TYPE projType = GetOwner()->Camera()->GetProjectionType();
	// 카메라 직교투영 배율 (Orthographic)
	float scale = GetOwner()->Camera()->GetScale();
	// 카메라 시야각 (Perspective)
	float fov = GetOwner()->Camera()->GetFOV();
	// 카메라 컴포넌트를 소유한 GameObjectdml 로컬상의 위치값
	Vec3 v3Pos = GetOwner()->Transform()->GetLocalPos();
	// 카메라 컴포넌트를 소유한 GameObject의 로컬상의 회전값
	Vec3 v3Rot = GetOwner()->Transform()->GetLocalRotation();
	// 카메라 컴포넌트를 소유한 GameObject의 로컬상의 바라보고있는 방향
	Vec3 v3RightX = GetOwner()->Transform()->GetLocalDirection(DIR_TYPE::RIGHT);
	Vec3 v3FrontZ = GetOwner()->Transform()->GetLocalDirection(DIR_TYPE::FRONT);
	// 마우스 드래그 방향
	Vec2 v2DragDir = M_KEY->GetMouseDragDir();

	// 카메라 투영 방식 변경 (직교투영 ↔ 원근투영)
	if (KEY_STATE::TAP == M_KEY->GetKeyState(KEY::P))
	{
		if (PROJ_TYPE::ORTHOGRAPHIC == projType)
		{
			GetOwner()->Camera()->SetProjectionType(PROJ_TYPE::PERSPECTIVE);
		}
		else
		{
			GetOwner()->Camera()->SetProjectionType(PROJ_TYPE::ORTHOGRAPHIC);
			GetOwner()->Transform()->SetLocalRotation(Vec3(0.f, 0.f, 0.f));
		}
	}

	// 위치이동 (상,하,좌,우)
	{
		// 상/전진
		if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::W))
		{
			if(PROJ_TYPE::ORTHOGRAPHIC == projType)
				v3Pos.y += (m_fCamSpeed * DT);
			if(PROJ_TYPE::PERSPECTIVE == projType)
				v3Pos += (v3FrontZ * m_fCamSpeed * DT);
		}
		// 하/후진
		if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::S))
		{
			if (PROJ_TYPE::ORTHOGRAPHIC == projType)
				v3Pos.y -= (m_fCamSpeed * DT);
			if (PROJ_TYPE::PERSPECTIVE == projType)
				v3Pos -= (v3FrontZ * m_fCamSpeed * DT);
		}
		// 좌
		if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::A))
		{
			if (PROJ_TYPE::ORTHOGRAPHIC == projType)
				v3Pos.x -= (m_fCamSpeed * DT);
			if (PROJ_TYPE::PERSPECTIVE == projType)
				v3Pos -= (v3RightX * m_fCamSpeed * DT);

		}
		// 우
		if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::D))
		{
			if (PROJ_TYPE::ORTHOGRAPHIC == projType)
				v3Pos.x += (m_fCamSpeed * DT);
			if (PROJ_TYPE::PERSPECTIVE == projType)
				v3Pos += (v3RightX * m_fCamSpeed * DT);
		}
		GetOwner()->Transform()->SetLocalPos(v3Pos);
	}
 

	// 회전이동 (조건 : 원근투영)
	if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::RBTN))
	{
		if (PROJ_TYPE::PERSPECTIVE == projType)
		{
			// 회전이동시 드래그 값의 변화값에서 
			// x의 변화량을 y에, y의 변화량을 x에 적용시키는 이유 : 
			// x축 방향으로 드래그하면 y축 기준으로 회전해야하고,
			// y축 방향으로 드래그하면 x축이 회전해야한다.
			v3Rot.x += (v2DragDir.y * (XM_PI / 180) * m_fDragSpeed * DT);
			v3Rot.y += (v2DragDir.x * (XM_PI / 180) * m_fDragSpeed * DT);
		}
		GetOwner()->Transform()->SetLocalRotation(v3Rot);
	}

	// 확대, 축소 (↑ : 120 , ↓ : -120)
	{
		// Zoom In
		if (M_KEY->GetMouseWheel() < 0)
		{
			if (PROJ_TYPE::ORTHOGRAPHIC == projType)
			{
				scale += (m_fWheelSpeed * DT);
			}
			if (PROJ_TYPE::PERSPECTIVE == projType)
			{
				fov += (m_fWheelSpeed * DT);
			}
		}
		// Zoom Out
		if (M_KEY->GetMouseWheel() > 0)
		{
			if (PROJ_TYPE::ORTHOGRAPHIC == projType)
			{
				scale -= (m_fWheelSpeed * DT);
			}
			if (PROJ_TYPE::PERSPECTIVE == projType)
			{
				fov -= (m_fWheelSpeed * DT);
			}
		}
		GetOwner()->Camera()->SetScale(scale);
		GetOwner()->Camera()->SetFOV(fov);
		M_KEY->SetMouseWheel(0);
	}

}

