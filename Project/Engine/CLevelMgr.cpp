#include "pch.h"
#include "CLevelMgr.h"

CLevelMgr::CLevelMgr()
	: m_pCurLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_pCurLevel)
	{
		delete m_pCurLevel;
		m_pCurLevel = nullptr;
	}
}

void CLevelMgr::Init()
{
	// 초기 레벨 구성하기
	m_pCurLevel = new CLevel;

	// Load Image
	{
		CTexture* pTex = M_ASSET->LoadTexture(L"bird", L"bird.png");
		pTex->SetName(L"bird");
		if (nullptr != pTex)
		{
			pTex->UpdateData(0);	// t0 레지스터에 바인딩
		}
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
		m_pTestObj->MeshRender()->GetMaterial()->m_tConst.iArr[0] = 1;

		//// Child1
		//{
		//	CGameObject* pChildObj = new CGameObject;
		//	pChildObj->SetName(L"ChildObj_Rec");
		//	pChildObj->AddComponent(new CTransform);
		//	pChildObj->AddComponent(new CMeshRender);
		//	pChildObj->Transform()->SetLocalPos(Vec3(100.f, 0.f, 0.f));
		//	pChildObj->Transform()->SetLocalScale(Vec3(50.f, 50.f, 1.f));
		//	pChildObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		//	pChildObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"DefaultMaterial"));
		//	m_pTestObj->AddChild(pChildObj);
		//	// Child2
		//	{
		//		CGameObject* pChildObj2 = new CGameObject;
		//		pChildObj2->SetName(L"ChildObj2_Rec");
		//		pChildObj2->AddComponent(new CTransform);
		//		pChildObj2->AddComponent(new CMeshRender);
		//		pChildObj2->Transform()->SetLocalPos(Vec3(50.f, 0.f, 0.f));
		//		pChildObj2->Transform()->SetLocalScale(Vec3(25.f, 25.f, 1.f));
		//		pChildObj2->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		//		pChildObj2->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"DefaultMaterial"));
		//		pChildObj->AddChild(pChildObj2);
		//	}
		//}
		GamePlayStatic::SpawnGameObject(m_pTestObj, LAYER_TYPE::LAYER_0);
	}
}

void CLevelMgr::Tick()
{
	if (nullptr == m_pCurLevel)
		return;

	m_pCurLevel->Clear();
	m_pCurLevel->Tick();
	m_pCurLevel->FinalTick();

	// test
	Test();
}

void CLevelMgr::FinalTick()
{
	m_pCurLevel->FinalTick();
}

void CLevelMgr::Render()
{
	if (nullptr != m_pCurLevel)
	{
		m_pCurLevel->Render();
	}
}

void CLevelMgr::Test()
{
	if (KEY_STATE::TAP == M_KEY->GetKeyState(KEY::C))
	{
		LAYER_TYPE type = m_pTestObj->GetLayer();
		CLayer* layer = m_pCurLevel->GetLayer(type);
		layer->RemoveObject(m_pTestObj);
	}

	if (KEY_STATE::TAP == M_KEY->GetKeyState(KEY::V))
	{
		LAYER_TYPE type = LAYER_TYPE::LAYER_1;
		CLayer* layer = m_pCurLevel->GetLayer(type);
		layer->AddObject(m_pTestObj, true);	// 자식객체도 부모객체의 레이어 따라감
	}
}
