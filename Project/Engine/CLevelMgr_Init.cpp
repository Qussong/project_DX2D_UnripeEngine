#include "pch.h"

void CLevelMgr::Init()
{
	// 초기 레벨 구성하기
	m_pCurLevel = new CLevel;

	// Load Image
	{
		Ptr<CTexture> pTex = nullptr;
		pTex = M_ASSET->LoadTexture(L"bluebird_hit", L"bluebird_hit.png");
		pTex = M_ASSET->LoadTexture(L"penguin_hit", L"penguin_hit.png");
	}

	// Camera
	{
		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"CameraObject");
		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CCamera);
		pObj->AddComponent(new CCameraScript);

		m_pCurLevel->AddObject(pObj, LAYER_TYPE::LAYER_0);
	}

	// Parent
	{
		m_pTestObj = new CGameObject;
		m_pTestObj->SetName(L"ParentObj_Rec");
		m_pTestObj->AddComponent(new CTransform);
		m_pTestObj->AddComponent(new CMeshRender);
		m_pTestObj->AddComponent(new CPlayerScript);

		m_pTestObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
		m_pTestObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));

		m_pTestObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		m_pTestObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"DefaultMaterial"));
		// texture
		Ptr<CTexture> pTex = M_ASSET->FindAsset<CTexture>(L"bluebird_hit");
		m_pTestObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);
		// scalar
		m_pTestObj->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_0, 1.f);

		// Child
		//{
		//	CGameObject* pChild = new CGameObject;
		//	pChild->SetName(L"ChildObj_Rec");
		//	pChild->AddComponent(new CTransform);
		//	pChild->AddComponent(new CMeshRender);

		//	pChild->Transform()->SetLocalPos(Vec3(50.f, 0.f, 0.f));
		//	pChild->Transform()->SetLocalScale(Vec3(50.f, 50.f, 1.f));

		//	pChild->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		//	pChild->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"ChildMaterial"));
		//	// texture
		//	Ptr<CTexture> pTex = M_ASSET->FindAsset<CTexture>(L"penguin_hit");
		//	pChild->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

		//	m_pTestObj->AddChild(pChild);
		//}

		GamePlayStatic::SpawnGameObject(m_pTestObj, LAYER_TYPE::LAYER_0);
	}
}