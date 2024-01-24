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

void CPlayerScript::Tick()
{
	CGameObject* owner = GetOwner();
	CTransform* transform = owner->Transform();
	Matrix matWorld = transform->GetWorldMatrix();

	bool posFlag = false;
	bool rotFlag = false;

	// local ��ǥ
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
		cout << "X " << (int)(v3Rot[0] * 180) << "��"
			<< "/Y " << (int)(v3Rot[1] * 180) << "��"
			<< "/Z " << (int)(v3Rot[2] * 180) << "��" << endl;
	}

	if (KEY_STATE::TAP == M_KEY->GetKeyState(KEY::SPACE))
	{
		CGameObject* pObj = nullptr;

		pObj = new CGameObject;
		pObj->SetName(L"Missile");
		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CMissileScript);

		Vec3 v3PlayerPos = GetOwner()->Transform()->GetLocalPos();
		pObj->Transform()->SetLocalPos(v3PlayerPos);
		pObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetGraphicShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"2D_DefaultShader"));

		GamePlayStatic::SpawnGameObject(pObj, LAYER_TYPE::LAYER_0);
	}

	transform->SetLocalPos(v3Pos);
	transform->SetLocalRotation(v3Rot);
}