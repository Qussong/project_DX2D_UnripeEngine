#include "pch.h"
#include "CEngine.h"

CEngine::CEngine()
	: m_hWnd(nullptr)
	, m_iWidth(0)
	, m_iHeight(0)

{
}

CEngine::~CEngine()
{
	uint32 size = m_vecObj.size();
	for (size_t i = 0; i < size; i++)
	{
		if (nullptr != m_vecObj[i])
		{
			delete m_vecObj[i];
			m_vecObj[i] = nullptr;
		}
	}
}

int CEngine::Init(HWND _hWnd, uint32 _width, uint32 _height)
{
	// member init
	m_hWnd = _hWnd;
	m_iWidth = _width;
	m_iHeight = _height;

	// Device, Context, SwapChain init
	CGraphics::GetInst()->Init(m_hWnd, m_iWidth, m_iHeight);

	// Manager init
	CTimeMgr::GetInst()->Init();
	CPathMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CAssetMgr::GetInst()->Init();

	// test_GameObject »ý¼º
	Test_GameObject();

	return S_OK;
}

void CEngine::Progress()
{
	Tick();
	Render();
}

void CEngine::Tick()
{
	// manager
	CTimeMgr::GetInst()->Tick();
	CKeyMgr::GetInst()->Tick();

	// test
	Test_tick();
}

void CEngine::Render()
{
	CGraphics::GetInst()->RenderBegin();

	// Rendering Pipeline
	{
		// test
		Test_render();
	}

	CGraphics::GetInst()->RenderEnd();
}

void CEngine::Test_tick()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
	{
		m_vecObj[i]->Tick();
		m_vecObj[i]->FinalTick();
	}
}

void CEngine::Test_render()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
	{
		m_vecObj[i]->Render();
	}
}

void CEngine::Test_GameObject()
{
	// Rect
	{
		CGameObject* obj = new CGameObject;

		obj->AddComponent(new CTransform);
		obj->AddComponent(new CMeshRender);

		obj->Transform()->SetRelativePos(Vec3(-0.5f, 0.f, 0.f));
		obj->Transform()->SetRelativeScale(Vec3(0.6f, 0.6f, 1.f));

		obj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		obj->MeshRender()->SetGraphicShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

		m_vecObj.push_back(obj);
	}

	// Circle
	{
		CGameObject* obj = new CGameObject;

		obj->AddComponent(new CTransform);
		obj->AddComponent(new CMeshRender);
		obj->AddComponent(new CPlayerScript);

		obj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
		obj->Transform()->SetRelativeScale(Vec3(0.6f, 0.6f, 1.f));

		obj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CircleMesh"));
		obj->MeshRender()->SetGraphicShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

		m_vecObj.push_back(obj);
	}

}
