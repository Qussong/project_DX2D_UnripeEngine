#include "pch.h"
#include "CPlayerScript.h"

CPlayerScript::CPlayerScript()
	: m_fSpeed(100.f)
{
	SetName(L"PlayerScript");
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Texture()
{
}

void CPlayerScript::Animation()
{
}

void CPlayerScript::Begin()
{
	Texture();
	Animation();
}

void CPlayerScript::Tick()
{
	CGameObject* owner = GetOwner();
	CTransform* transform = owner->Transform();
	Matrix matWorld = transform->GetWorldMatrix();

	bool posFlag = false;
	bool rotFlag = false;

	// local ÁÂÇ¥
	Vec3 v3Scale = transform->GetLocalScale();
	Vec3 v3Rot = transform->GetLocalRotation();
	Vec3 v3Pos = transform->GetLocalPos();

	// Position
	if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::LEFT))
	{
		v3Pos.x -= m_fSpeed * DT;
		posFlag = true;
	}
	if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::RIGHT))
	{
		v3Pos.x += m_fSpeed * DT;
		posFlag = true;
	}
	if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::UP))
	{
		v3Pos.y += m_fSpeed * DT;
		posFlag = true;
	}
	if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::DOWN))
	{
		v3Pos.y -= m_fSpeed * DT;
		posFlag = true;
	}


	// Rotation
	if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::LCTRL))
	{
		if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::X))
		{
			v3Rot.x -= DT * XM_PI;
			rotFlag = true;
		}
		if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::Y))
		{
			v3Rot.y -= DT * XM_PI;
			rotFlag = true;
		}
		if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::Z))
		{
			v3Rot.z -= DT * XM_PI;
			rotFlag = true;
		}
	}
	else
	{
		if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::X))
		{
			v3Rot.x += DT * XM_PI;
			rotFlag = true;
		}
		if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::Y))
		{
			v3Rot.y += DT * XM_PI;
			rotFlag = true;
		}
		if (KEY_STATE::PRESSED == M_KEY->GetKeyState(KEY::Z))
		{
			v3Rot.z += DT * XM_PI;
			rotFlag = true;
		}
	}

	// monitoring
	if (posFlag)
	{
		cout << "X " << (int)(v3Pos[0] * GRAPHICS->GetResolution().x / 2)
			<< "/Y " << (int)(v3Pos[1] * GRAPHICS->GetResolution().y / 2) << endl;
	}
	if (rotFlag)
	{
		cout << "X " << (int)(v3Rot[0] * 180) << "¨¬"
			<< "/Y " << (int)(v3Rot[1] * 180) << "¨¬"
			<< "/Z " << (int)(v3Rot[2] * 180) << "¨¬" << endl;
	}

	if (KEY_STATE::TAP == M_KEY->GetKeyState(KEY::SPACE))
	{
		Ptr<CMaterial> pMtrl = GetOwner()->MeshRender()->GetMaterial();
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 1);
		}
	}
	else if(KEY_STATE::RELEASED == M_KEY->GetKeyState(KEY::SPACE))
	{
		Ptr<CMaterial> pMtrl = GetOwner()->MeshRender()->GetMaterial();
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 0);
		}
	}

	transform->SetLocalPos(v3Pos);
	transform->SetLocalRotation(v3Rot);
}

void CPlayerScript::BeginOverlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider)
{
	int a = 0;
	//_otherObj->Destroy();
}

void CPlayerScript::Overlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider)
{
}

void CPlayerScript::EndOverlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider)
{
	int a = 0;
}
