#include "pch.h"
#include "CLevelMgr.h"

CLevelMgr::CLevelMgr()
	: m_pCurLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()
{
	// temp
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
		m_pTestObjet = new CGameObject;
		m_pTestObjet->SetName(L"ParentObj_Rec");
		m_pTestObjet->AddComponent(new CTransform);
		m_pTestObjet->AddComponent(new CMeshRender);
		m_pTestObjet->AddComponent(new CPlayerScript);

		m_pTestObjet->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
		m_pTestObjet->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));

		m_pTestObjet->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		m_pTestObjet->MeshRender()->SetGraphicShader(M_ASSET->FindAsset<CGraphicShader>(L"2D_DefaultShader"));

		// Child1
		{
			CGameObject* pChildObj = new CGameObject;
			pChildObj->SetName(L"ChildObj_Rec");
			pChildObj->AddComponent(new CTransform);
			pChildObj->AddComponent(new CMeshRender);

			pChildObj->Transform()->SetLocalPos(Vec3(100.f, 0.f, 0.f));
			pChildObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));

			pChildObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
			pChildObj->MeshRender()->SetGraphicShader(M_ASSET->FindAsset<CGraphicShader>(L"2D_DefaultShader"));
			
			m_pTestObjet->AddChild(pChildObj);

			// Child2
			{
				CGameObject* pChildObj2 = new CGameObject;
				pChildObj2->SetName(L"ChildObj2_Rec");
				pChildObj2->AddComponent(new CTransform);
				pChildObj2->AddComponent(new CMeshRender);

				pChildObj2->Transform()->SetLocalPos(Vec3(100.f, 0.f, 0.f));
				pChildObj2->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));

				pChildObj2->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
				pChildObj2->MeshRender()->SetGraphicShader(M_ASSET->FindAsset<CGraphicShader>(L"2D_DefaultShader"));

				pChildObj->AddChild(pChildObj2);
			}
		}
		m_pCurLevel->AddObject(m_pTestObjet, LAYER_TYPE::LAYER_0);
	}
}

void CLevelMgr::Tick()
{
	if (nullptr != m_pCurLevel)
	{
		m_pCurLevel->Tick();
		FinalTick();
	}

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
		LAYER_TYPE type = m_pTestObjet->GetLayer();
		CLayer* layer = m_pCurLevel->GetLayer(type);
		layer->RemoveObject(m_pTestObjet);
	}

	if (KEY_STATE::TAP == M_KEY->GetKeyState(KEY::V))
	{
		LAYER_TYPE type = LAYER_TYPE::LAYER_1;
		CLayer* layer = m_pCurLevel->GetLayer(type);
		layer->RegisterObject(m_pTestObjet);
	}
}
