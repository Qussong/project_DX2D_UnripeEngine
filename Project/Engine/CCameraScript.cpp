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
	// ī�޶� ���� Ÿ��
	PROJ_TYPE projType = GetOwner()->Camera()->GetProjectionType();
	// ī�޶� ������Ʈ�� ������ GameObjectdml ���û��� ��ġ��
	Vec3 v3Pos = GetOwner()->Transform()->GetRelativePos();
	// ī�޶� ������Ʈ�� ������ GameObjectdml ���û��� ȸ����
	Vec3 v3Rot = GetOwner()->Transform()->GetRelativeRotation();
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

	// ȸ���̵� (���� : ��������)
	if (PROJ_TYPE::PERSPECTIVE == projType)
	{
		if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::RBTN))
		{
			// ȸ���̵��� �巡�� ���� ��ȭ������ 
			// x�� ��ȭ���� y��, y�� ��ȭ���� x�� �����Ű�� ���� : 
			// x�� �������� �巡���ϸ� y�� �������� ȸ���ؾ��ϰ�,
			// y�� �������� �巡���ϸ� x���� ȸ���ؾ��Ѵ�.
			v3Rot.x += (v2DragDir.y * (XM_PI / 180) * m_fDragSpeed * DT);
			v3Rot.y += (v2DragDir.x * (XM_PI / 180) * m_fDragSpeed * DT);
		}
	}

	// Ȯ��, ���



	GetOwner()->Transform()->SetRelativePos(v3Pos);
	GetOwner()->Transform()->SetRelativeRotation(v3Rot);
}
