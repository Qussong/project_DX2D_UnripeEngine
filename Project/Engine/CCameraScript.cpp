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

	// FOV (Ȯ��, ���)
}
