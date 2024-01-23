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

		m_pCurLevel->AddObject(pObj, 0);
	}

	// Parent
	{
		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"ParentObj_Rec");
		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CPlayerScript);

		pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
		pObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));

		pObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetGraphicShader(M_ASSET->FindAsset<CGraphicShader>(L"2D_DefaultShader"));

		// Child
		{
			CGameObject* pChildObj = new CGameObject;
			pChildObj->SetName(L"ChildObj_Rec");
			pChildObj->AddComponent(new CTransform);
			pChildObj->AddComponent(new CMeshRender);

			pChildObj->Transform()->SetLocalPos(Vec3(100.f, 0.f, 0.f));
			pChildObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));

			pChildObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
			pChildObj->MeshRender()->SetGraphicShader(M_ASSET->FindAsset<CGraphicShader>(L"2D_DefaultShader"));
			
			pObj->AddChild(pChildObj);
		}
		m_pCurLevel->AddObject(pObj, 0);
	}
}

void CLevelMgr::Tick()
{
	if (nullptr != m_pCurLevel)
	{
		m_pCurLevel->Tick();
		FinalTick();
	}
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
