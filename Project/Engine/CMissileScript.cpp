#include "pch.h"
#include "CMissileScript.h"

CMissileScript::CMissileScript()
	: m_fSpeed(100.f)
	, m_v2Dir{}
{
}

CMissileScript::~CMissileScript()
{
}

void CMissileScript::Tick()
{
	CTransform* transform = GetOwner()->Transform();
	Vec3 v3LocalPos = transform->GetLocalPos();

	v3LocalPos.x += (m_v2Dir.x * m_fSpeed * DT);
	v3LocalPos.y += (m_v2Dir.y * m_fSpeed * DT);
	transform->SetLocalPos(v3LocalPos);
}
