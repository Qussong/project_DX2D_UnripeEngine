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
		CTexture* pTex = M_ASSET->LoadTexture(L"poketmon", L"cat.png");
		pTex->SetName(L"파이리");
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

	// Circle
	{
		//CGameObject* pObj = new CGameObject;
		//pObj->SetName(L"CircleObject");
		//pObj->AddComponent(new CTransform);
		//pObj->AddComponent(new CMeshRender);

		//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
		//pObj->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));

		//pObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"CircleMesh"));
		//pObj->MeshRender()->SetGraphicShader(M_ASSET->FindAsset<CGraphicShader>(L"2D_WireframeShader"));

		//m_pCurLevel->AddObject(pObj, 0);
	}

	// Rect
	{
		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"RectObject");
		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CPlayerScript);

		pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
		pObj->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));

		pObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetGraphicShader(M_ASSET->FindAsset<CGraphicShader>(L"2D_DefaultShader"));

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
