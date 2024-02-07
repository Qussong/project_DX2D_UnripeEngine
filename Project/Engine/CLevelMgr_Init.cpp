#include "pch.h"

void CLevelMgr::Init()
{
	// 초기 레벨 구성하기
	m_pCurLevel = new CLevel;

	// 충돌 설정
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
		// BasicComp
		pCamObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
		pCamObj->Transform()->SetLocalRotation(Vec3(0.f, 0.f, 0.f));
		pCamObj->Camera()->SetPriority(0);
		pCamObj->Camera()->LayerCheckAll(/*true*/);
		pCamObj->Camera()->LayerCheck(L"UILayer", false);
		
		m_pCurLevel->AddObject(pCamObj, LAYER_TYPE::DEFAULT);
	}

	// UI Camera
	{
		CGameObject* pCamObj = new CGameObject;
		pCamObj->SetName(L"UICamera");
		pCamObj->AddComponent(new CTransform);
		pCamObj->AddComponent(new CCamera);
		// BasicComp
		pCamObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
		pCamObj->Transform()->SetLocalRotation(Vec3(0.f, 0.f, 0.f));
		pCamObj->Camera()->SetPriority(1);
		pCamObj->Camera()->LayerCheck(L"UILayer", true);

		m_pCurLevel->AddObject(pCamObj, LAYER_TYPE::DEFAULT);
	}

	// PlayerObj
	{
		CGameObject* pPlayerObj = new CGameObject;
		pPlayerObj->SetName(L"PlayerObj");
		pPlayerObj->AddComponent(new CTransform);
		pPlayerObj->AddComponent(new CMeshRender);
		pPlayerObj->AddComponent(new CPlayerScript);
		pPlayerObj->AddComponent(new CCollider2D);
		pPlayerObj->AddComponent(new CAnimator2D);
		// BasicComp
		pPlayerObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
		pPlayerObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));
		pPlayerObj->Collider2D()->SetAbsolute(true);	// true = 부모 Scale 영향 안받음
		pPlayerObj->Collider2D()->SetOffsetScale(Vec2(30.f, 30.f));
		pPlayerObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
		pPlayerObj->Collider2D()->SetColliderType(COLLIDER2D_TYPE::CIRCLE);
		// RenderComp
		pPlayerObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		pPlayerObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"DefaultMaterial"));

		GamePlayStatic::SpawnGameObject(pPlayerObj, LAYER_TYPE::PLAYER);
	}

	// MonsterObj
	{
		CGameObject* pMonsterObj = new CGameObject;
		pMonsterObj->SetName(L"MonsterObj");
		pMonsterObj->AddComponent(new CTransform);
		pMonsterObj->AddComponent(new CMeshRender);
		pMonsterObj->AddComponent(new CCollider2D);
		pMonsterObj->AddComponent(new CAnimator2D);
		pMonsterObj->AddComponent(new CTestMonsterScript);
		// BasicComp
		pMonsterObj->Transform()->SetLocalPos(Vec3(100.f, 0.f, 500.f));
		pMonsterObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));
		pMonsterObj->Collider2D()->SetAbsolute(true);	// true = 부모 Scale 영향 안받음
		pMonsterObj->Collider2D()->SetOffsetScale(Vec2(30.f, 30.f));
		pMonsterObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
		pMonsterObj->Collider2D()->SetColliderType(COLLIDER2D_TYPE::CIRCLE);
		// RenderComp
		pMonsterObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		pMonsterObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"MonsterMaterial"));

		GamePlayStatic::SpawnGameObject(pMonsterObj, LAYER_TYPE::MONSTER);
	}

	// Background
	{
		CGameObject* pBackObj = new CGameObject;
		pBackObj->SetName(L"Background");
		pBackObj->AddComponent(new CTransform);
		pBackObj->AddComponent(new CMeshRender);
		// BasicComp
		pBackObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 600.f));
		pBackObj->Transform()->SetLocalScale(Vec3(500.f, 500.f, 1.f));
		pBackObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		pBackObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"BackgroundMaterial"));
		// texture
		Ptr<CTexture> pTex = M_ASSET->FindAsset<CTexture>(L"flower");
		pBackObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

		GamePlayStatic::SpawnGameObject(pBackObj, LAYER_TYPE::BACKGROUND);
	}

	// LightObj_POINT1
	{
		CGameObject* pLightObj = new CGameObject;
		pLightObj->SetName(L"Light_Point1");
		pLightObj->AddComponent(new CTransform);
		pLightObj->AddComponent(new CMeshRender);
		pLightObj->AddComponent(new CLight2D);
		// basicComp
		pLightObj->Transform()->SetLocalPos(Vec3(-50.f, -50.f, 500.f));
		pLightObj->Light2D()->SetLightType(LIGHT_TYPE::POINT);
		pLightObj->Light2D()->SetLightColor(Vec3(1.f, 0.f, 0.f));
		pLightObj->Light2D()->SetRaius(150.f);

		GamePlayStatic::SpawnGameObject(pLightObj, LAYER_TYPE::LIGHT2D);
	}

	// LightObj_POINT2
	{
		CGameObject* pLightObj = new CGameObject;
		pLightObj->SetName(L"Light_Point2");
		pLightObj->AddComponent(new CTransform);
		pLightObj->AddComponent(new CMeshRender);
		pLightObj->AddComponent(new CLight2D);
		// basicComp
		pLightObj->Transform()->SetLocalPos(Vec3(50.f, -50.f, 500.f));
		pLightObj->Light2D()->SetLightType(LIGHT_TYPE::POINT);
		pLightObj->Light2D()->SetLightColor(Vec3(0.f, 1.f, 0.f));
		pLightObj->Light2D()->SetRaius(150.f);

		GamePlayStatic::SpawnGameObject(pLightObj, LAYER_TYPE::LIGHT2D);
	}

	// LightObj_POINT3
	{
		CGameObject* pLightObj = new CGameObject;
		pLightObj->SetName(L"Light_Point2");
		pLightObj->AddComponent(new CTransform);
		pLightObj->AddComponent(new CMeshRender);
		pLightObj->AddComponent(new CLight2D);
		// basicComp
		pLightObj->Transform()->SetLocalPos(Vec3(0.f, 70.f, 500.f));
		pLightObj->Light2D()->SetLightType(LIGHT_TYPE::POINT);
		pLightObj->Light2D()->SetLightColor(Vec3(0.f, 0.f, 1.f));
		pLightObj->Light2D()->SetRaius(150.f);

		GamePlayStatic::SpawnGameObject(pLightObj, LAYER_TYPE::LIGHT2D);
	}

	// LightObj_DIRECTIONAL
	{
		CGameObject* pLightObj = new CGameObject;
		pLightObj->SetName(L"Light_Directional");
		pLightObj->AddComponent(new CTransform);
		pLightObj->AddComponent(new CMeshRender);
		pLightObj->AddComponent(new CLight2D);
		// basicComp
		pLightObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
		pLightObj->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
		pLightObj->Light2D()->SetAmbient(Vec4(0.3f, 0.3f, 0.3f, 0.3f));

		GamePlayStatic::SpawnGameObject(pLightObj, LAYER_TYPE::LIGHT2D);
	}

	// UIObj
	{
		CGameObject* pUIObj = new CGameObject;
		pUIObj->SetName(L"UI");
		pUIObj->AddComponent(new CTransform);
		pUIObj->AddComponent(new CMeshRender);
		// basicComp
		pUIObj->Transform()->SetLocalPos(Vec3(-600.f, 300.f, 500.f));
		pUIObj->Transform()->SetLocalScale(Vec3(55.f, 50.f, 1.f));
		// renderComp
		pUIObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		pUIObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"UIMaterial"));
		// texture
		Ptr<CTexture> pTex = M_ASSET->FindAsset<CTexture>(L"bluebird");
		pUIObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

		GamePlayStatic::SpawnGameObject(pUIObj, LAYER_TYPE::UI);
	}
}