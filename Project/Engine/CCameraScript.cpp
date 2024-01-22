#include "pch.h"
#include "CCameraScript.h"

CCameraScript::CCameraScript()
	: m_fCamSpeed(100.f)
	, m_fDragSpeed(5.f * 180.f)
	, m_fWheelSpeed(50.f)
{
}

CCameraScript::~CCameraScript()
{
}

void CCameraScript::Tick()
{
	// ī�޶� ���� Ÿ��
	PROJ_TYPE projType = GetOwner()->Camera()->GetProjectionType();
	// ī�޶� �������� ���� (Orthographic)
	float scale = GetOwner()->Camera()->GetScale();
	// ī�޶� �þ߰� (Perspective)
	float fov = GetOwner()->Camera()->GetFOV();
	// ī�޶� ������Ʈ�� ������ GameObjectdml ���û��� ��ġ��
	Vec3 v3Pos = GetOwner()->Transform()->GetRelativePos();
	// ī�޶� ������Ʈ�� ������ GameObject�� ���û��� ȸ����
	Vec3 v3Rot = GetOwner()->Transform()->GetRelativeRotation();
	// ī�޶� ������Ʈ�� ������ GameObject�� ���û��� �ٶ󺸰��ִ� ����
	Vec3 v3RightX = GetOwner()->Transform()->GetDirection(DIR_TYPE::RIGHT);
	Vec3 v3FrontZ = GetOwner()->Transform()->GetDirection(DIR_TYPE::FRONT);
	// ���콺 �巡�� ����
	Vec2 v2DragDir = CKeyMgr::GetInst()->GetMouseDragDir();

	// ī�޶� ���� ��� ���� (�������� �� ��������)
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

	// ��ġ�̵� (��,��,��,��)
	{
		// ��/����
		if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::W))
		{
			if(PROJ_TYPE::ORTHOGRAPHIC == projType)
				v3Pos.y += (m_fCamSpeed * DT);
			if(PROJ_TYPE::PERSPECTIVE == projType)
				v3Pos += (v3FrontZ * m_fCamSpeed * DT);
		}
		// ��/����
		if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::S))
		{
			if (PROJ_TYPE::ORTHOGRAPHIC == projType)
				v3Pos.y -= (m_fCamSpeed * DT);
			if (PROJ_TYPE::PERSPECTIVE == projType)
				v3Pos -= (v3FrontZ * m_fCamSpeed * DT);
		}
		// ��
		if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::A))
		{
			if (PROJ_TYPE::ORTHOGRAPHIC == projType)
				v3Pos.x -= (m_fCamSpeed * DT);
			if (PROJ_TYPE::PERSPECTIVE == projType)
				v3Pos -= (v3RightX * m_fCamSpeed * DT);

		}
		// ��
		if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::D))
		{
			if (PROJ_TYPE::ORTHOGRAPHIC == projType)
				v3Pos.x += (m_fCamSpeed * DT);
			if (PROJ_TYPE::PERSPECTIVE == projType)
				v3Pos += (v3RightX * m_fCamSpeed * DT);
		}
		GetOwner()->Transform()->SetRelativePos(v3Pos);
	}
 

	// ȸ���̵� (���� : ��������)
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::RBTN))
	{
		if (PROJ_TYPE::PERSPECTIVE == projType)
		{
			// ȸ���̵��� �巡�� ���� ��ȭ������ 
			// x�� ��ȭ���� y��, y�� ��ȭ���� x�� �����Ű�� ���� : 
			// x�� �������� �巡���ϸ� y�� �������� ȸ���ؾ��ϰ�,
			// y�� �������� �巡���ϸ� x���� ȸ���ؾ��Ѵ�.
			v3Rot.x += (v2DragDir.y * (XM_PI / 180) * m_fDragSpeed * DT);
			v3Rot.y += (v2DragDir.x * (XM_PI / 180) * m_fDragSpeed * DT);
		}
		GetOwner()->Transform()->SetRelativeRotation(v3Rot);
	}

	// Ȯ��, ��� (�� : 120 , �� : -120)
	{
		// Zoom In
		if (CKeyMgr::GetInst()->GetMouseWheel() < 0)
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
		if (CKeyMgr::GetInst()->GetMouseWheel() > 0)
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
		CKeyMgr::GetInst()->SetMouseWheel(0.f);
	}

}

