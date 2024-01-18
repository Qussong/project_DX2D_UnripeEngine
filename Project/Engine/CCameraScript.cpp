#include "pch.h"
#include "CCameraScript.h"

CCameraScript::CCameraScript()
	: m_fCamSpeed(1.f)
	, m_fDragSpeed(3.f * 180.f)
{
}

CCameraScript::~CCameraScript()
{
}

void CCameraScript::Tick()
{
	// ī�޶� ������Ʈ�� ������ GameObjectdml ���û��� ��ġ��
	Vec3 v3Pos = GetOwner()->Transform()->GetRelativePos();

	// ��ġ�̵� (��,��,��,��)
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

	// ȸ���̵�
	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::RBTN))
	{
		Vec3 v3Rot = GetOwner()->Transform()->GetRelativeRotation();
		Vec2 v2DragDir = CKeyMgr::GetInst()->GetMouseDragDir();

		v3Rot.x += (v2DragDir.x * (XM_PI / 180) * m_fDragSpeed * DT);
		v3Rot.y += (v2DragDir.y * (XM_PI / 180) * m_fDragSpeed * DT);
		GetOwner()->Transform()->SetRelativeRotation(v3Rot);
	}

	// FOV (Ȯ��, ���)

}
