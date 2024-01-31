#include "pch.h"

void CLevelMgr::Init()
{
	// 초기 레벨 구성하기
	{
		m_pCurLevel = new CLevel;
		m_pCurLevel->GetLayer(LAYER_TYPE::DEFAULT)->SetName(L"DefaultLayer");
		m_pCurLevel->GetLayer(LAYER_TYPE::BACKGROUND)->SetName(L"BackgroundLayer");
		m_pCurLevel->GetLayer(LAYER_TYPE::TILE)->SetName(L"TileLayer");
		m_pCurLevel->GetLayer(LAYER_TYPE::PLAYER)->SetName(L"PlayerLayer");
		m_pCurLevel->GetLayer(LAYER_TYPE::MONSTER)->SetName(L"MonsterLayer");
		m_pCurLevel->GetLayer(LAYER_TYPE::UI)->SetName(L"UILayer");
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
		//pCamObj->Camera()->LayerCheckByName(L"UILayer", false);

		m_pCurLevel->AddObject(pCamObj, LAYER_TYPE::DEFAULT);
	}

	// Load Image
	{
		Ptr<CTexture> pTex = nullptr;
		pTex = M_ASSET->LoadTexture(L"bluebird_hit", L"bluebird_hit.png");
		pTex = M_ASSET->LoadTexture(L"penguin_hit", L"penguin_hit.png");
	}

	// PlayerObj
	{
		m_pTestObj = new CGameObject;
		m_pTestObj->SetName(L"ParentObj_Rec");
		m_pTestObj->AddComponent(new CTransform);
		m_pTestObj->AddComponent(new CMeshRender);
		m_pTestObj->AddComponent(new CPlayerScript);
		// basicComp
		m_pTestObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
		m_pTestObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));
		// render
		m_pTestObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		m_pTestObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"DefaultMaterial"));
		// texture
		Ptr<CTexture> pTex = M_ASSET->FindAsset<CTexture>(L"bluebird_hit");
		m_pTestObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);
		// scalar
		m_pTestObj->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_0, 1.f);

		GamePlayStatic::SpawnGameObject(m_pTestObj, LAYER_TYPE::PLAYER);
	}

	// UIObj
	{
		CGameObject* pUIObj = new CGameObject;
		pUIObj->SetName(L"UI");
		pUIObj->AddComponent(new CTransform);
		pUIObj->AddComponent(new CMeshRender);
		// basicComp
		pUIObj->Transform()->SetLocalPos(Vec3(-550.f, 300.f, 500.f));
		pUIObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));
		// render
		pUIObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		pUIObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"UIMaterial"));
		// texture
		Ptr<CTexture> pTex = M_ASSET->FindAsset<CTexture>(L"penguin_hit");
		pUIObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

		GamePlayStatic::SpawnGameObject(pUIObj, LAYER_TYPE::UI);
	}
}