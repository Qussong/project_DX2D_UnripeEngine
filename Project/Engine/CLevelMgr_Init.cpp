#include "pch.h"

void CLevelMgr::Init()
{
	// �ʱ� ���� �����ϱ�
	{
		m_pCurLevel = new CLevel;
		m_pCurLevel->GetLayer(LAYER_TYPE::DEFAULT)->SetName(L"DefaultLayer");
		m_pCurLevel->GetLayer(LAYER_TYPE::BACKGROUND)->SetName(L"BackgroundLayer");
		m_pCurLevel->GetLayer(LAYER_TYPE::TILE)->SetName(L"TileLayer");
		m_pCurLevel->GetLayer(LAYER_TYPE::PLAYER)->SetName(L"PlayerLayer");
		m_pCurLevel->GetLayer(LAYER_TYPE::MONSTER)->SetName(L"MonsterLayer");
		m_pCurLevel->GetLayer(LAYER_TYPE::UI)->SetName(L"UILayer");
	}

	// �浹 ����
	{
		M_COLLISION->LayerCheck(L"PlayerLayer", L"MonsterLayer");
		M_COLLISION->LayerCheck(L"MonsterLayer", L"MonsterLayer");
	}

	// Main Camera
	{
		CGameObject* pCamObj = new CGameObject;
		pCamObj->SetName(L"MainCamera");
		pCamObj->AddComponent(new CTransform);
		pCamObj->AddComponent(new CCamera);
		pCamObj->AddComponent(new CCameraScript);

		pCamObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
		pCamObj->Transform()->SetLocalRotation(Vec3(0.f, 0.f, 0.f));

		pCamObj->Camera()->SetPriority(0);
		pCamObj->Camera()->LayerCheckAll(/*true*/);
		//pCamObj->Camera()->LayerCheck(L"UILayer", false);

		m_pCurLevel->AddObject(pCamObj, LAYER_TYPE::DEFAULT);
	}

	// PlayerObj
	{
		m_pTestObj = new CGameObject;
		m_pTestObj->SetName(L"PlayerObj");
		m_pTestObj->AddComponent(new CTransform);
		m_pTestObj->AddComponent(new CMeshRender);
		m_pTestObj->AddComponent(new CPlayerScript);
		m_pTestObj->AddComponent(new CCollider2D);
		// basicComp
		m_pTestObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
		m_pTestObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));
		m_pTestObj->Collider2D()->SetAbsolute(true);	// true = �θ� Scale ���� �ȹ���
		m_pTestObj->Collider2D()->SetOffsetScale(Vec2(50.f, 50.f));
		m_pTestObj->Collider2D()->SetOffsetPos(Vec2(6.f, 3.f));
		m_pTestObj->Collider2D()->SetColliderType(COLLIDER2D_TYPE::CIRCLE);
		// renderComp
		m_pTestObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		m_pTestObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"DefaultMaterial"));
		// texture
		Ptr<CTexture> pTex = M_ASSET->FindAsset<CTexture>(L"bluebird_hit");
		m_pTestObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

		GamePlayStatic::SpawnGameObject(m_pTestObj, LAYER_TYPE::PLAYER);
	}

	// MonsterObj
	{
		CGameObject* pMonsterObj = new CGameObject;
		pMonsterObj->SetName(L"MonsterObj");
		pMonsterObj->AddComponent(new CTransform);
		pMonsterObj->AddComponent(new CMeshRender);
		pMonsterObj->AddComponent(new CCollider2D);
		// basicComp_Transform, Collider
		pMonsterObj->Transform()->SetLocalPos(Vec3(100.f, 50.f, 500.f));
		pMonsterObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));
		pMonsterObj->Collider2D()->SetAbsolute(true);	// true = �θ� Scale ���� �ȹ���
		pMonsterObj->Collider2D()->SetOffsetScale(Vec2(50.f, 50.f));
		pMonsterObj->Collider2D()->SetOffsetPos(Vec2(6.f, 3.f));
		pMonsterObj->Collider2D()->SetColliderType(COLLIDER2D_TYPE::CIRCLE);
		// renderComp
		pMonsterObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		pMonsterObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"MonsterMaterial"));
		// texture
		Ptr<CTexture> pTex = M_ASSET->FindAsset<CTexture>(L"penguin_hit");
		pMonsterObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

		GamePlayStatic::SpawnGameObject(pMonsterObj, LAYER_TYPE::MONSTER);
	}

	// MonsterObj
	{
		CGameObject* pMonsterObj = new CGameObject;
		pMonsterObj->SetName(L"MonsterObj");
		pMonsterObj->AddComponent(new CTransform);
		pMonsterObj->AddComponent(new CMeshRender);
		pMonsterObj->AddComponent(new CCollider2D);
		// basicComp_Transform, Collider
		pMonsterObj->Transform()->SetLocalPos(Vec3(100.f, -50.f, 500.f));
		pMonsterObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));
		pMonsterObj->Collider2D()->SetAbsolute(true);	// true = �θ� Scale ���� �ȹ���
		pMonsterObj->Collider2D()->SetOffsetScale(Vec2(50.f, 50.f));
		pMonsterObj->Collider2D()->SetOffsetPos(Vec2(6.f, 3.f));
		// renderComp
		pMonsterObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		pMonsterObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"MonsterMaterial"));
		// texture
		Ptr<CTexture> pTex = M_ASSET->FindAsset<CTexture>(L"penguin_hit");
		pMonsterObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

		GamePlayStatic::SpawnGameObject(pMonsterObj, LAYER_TYPE::MONSTER);
	}

	// UIObj
	//{
	//	CGameObject* pUIObj = new CGameObject;
	//	pUIObj->SetName(L"UI");
	//	pUIObj->AddComponent(new CTransform);
	//	pUIObj->AddComponent(new CMeshRender);
	//	// basicComp
	//	pUIObj->Transform()->SetLocalPos(Vec3(-550.f, 300.f, 500.f));
	//	pUIObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));
	//	// renderComp
	//	pUIObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
	//	pUIObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"UIMaterial"));
	//	// texture
	//	Ptr<CTexture> pTex = M_ASSET->FindAsset<CTexture>(L"test");
	//	pUIObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

	//	GamePlayStatic::SpawnGameObject(pUIObj, LAYER_TYPE::UI);
	//}
}