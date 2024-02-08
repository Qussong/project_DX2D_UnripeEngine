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
	// ī�޶� ���� Ÿ��
	PROJ_TYPE projType = GetOwner()->Camera()->GetProjectionType();
	// ī�޶� �������� ���� (Orthographic)
	float scale = GetOwner()->Camera()->GetScale();
	// ī�޶� �þ߰� (Perspective)
	float fov = GetOwner()->Camera()->GetFOV();
	// ī�޶� ������Ʈ�� ������ GameObjectdml ���û��� ��ġ��
	Vec3 v3Pos = GetOwner()->Transform()->GetLocalPos();
	// ī�޶� ������Ʈ�� ������ GameObject�� ���û��� ȸ����
	Vec3 v3Rot = GetOwner()->Transform()->GetLocalRotation();
	// ī�޶� ������Ʈ�� ������ GameObject�� ���û��� �ٶ󺸰��ִ� ����
	Vec3 v3RightX = GetOwner()->Transform()->GetLocalDirection(DIR_TYPE::RIGHT);
	Vec3 v3FrontZ = GetOwner()->Transform()->GetLocalDirection(DIR_TYPE::FRONT);
	// ���콺 �巡�� ����
	Vec2 v2DragDir = M_KEY->GetMouseDragDir();

	// ī�޶� ���� ��� ���� (�������� �� ��������)
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

	// ��ġ�̵� (��,��,��,��)
	{
		// ��/����
		if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::W))
		{
			if(PROJ_TYPE::ORTHOGRAPHIC == projType)
				v3Pos.y += (m_fCamSpeed * DT);
			if(PROJ_TYPE::PERSPECTIVE == projType)
				v3Pos += (v3FrontZ * m_fCamSpeed * DT);
		}
		// ��/����
		if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::S))
		{
			if (PROJ_TYPE::ORTHOGRAPHIC == projType)
				v3Pos.y -= (m_fCamSpeed * DT);
			if (PROJ_TYPE::PERSPECTIVE == projType)
				v3Pos -= (v3FrontZ * m_fCamSpeed * DT);
		}
		// ��
		if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::A))
		{
			if (PROJ_TYPE::ORTHOGRAPHIC == projType)
				v3Pos.x -= (m_fCamSpeed * DT);
			if (PROJ_TYPE::PERSPECTIVE == projType)
				v3Pos -= (v3RightX * m_fCamSpeed * DT);

		}
		// ��
		if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::D))
		{
			if (PROJ_TYPE::ORTHOGRAPHIC == projType)
				v3Pos.x += (m_fCamSpeed * DT);
			if (PROJ_TYPE::PERSPECTIVE == projType)
				v3Pos += (v3RightX * m_fCamSpeed * DT);
		}
		GetOwner()->Transform()->SetLocalPos(v3Pos);
	}
 

	// ȸ���̵� (���� : ��������)
	if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::RBTN))
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
		GetOwner()->Transform()->SetLocalRotation(v3Rot);
	}

	// Ȯ��, ��� (�� : 120 , �� : -120)
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

