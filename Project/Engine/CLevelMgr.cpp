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

	// Rect
	{
		CGameObject* pObj = new CGameObject;

		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);

		pObj->Transform()->SetRelativePos(Vec3(-0.5f, 0.f, 0.f));
		pObj->Transform()->SetRelativeScale(Vec3(0.6f, 0.6f, 1.f));

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetGraphicShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

		m_pCurLevel->AddObject(pObj, 0);
	}

	// Circle
	{
		CGameObject* pObj = new CGameObject;

		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CPlayerScript);

		pObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
		pObj->Transform()->SetRelativeScale(Vec3(0.6f, 0.6f, 1.f));

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CircleMesh"));
		pObj->MeshRender()->SetGraphicShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

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
