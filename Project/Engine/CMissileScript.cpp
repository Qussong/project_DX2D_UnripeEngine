#include "pch.h"
#include "CMissileScript.h"

CMissileScript::CMissileScript()
	: m_fSpeed(500.f)
{
}

CMissileScript::~CMissileScript()
{
}

void CMissileScript::Tick()
{
	CTransform* transform = GetOwner()->Transform();
	Vec3 v3LocalPos = transform->GetLocalPos();

	v3LocalPos.y += (m_fSpeed * DT);

	transform->SetLocalPos(v3LocalPos);
}
