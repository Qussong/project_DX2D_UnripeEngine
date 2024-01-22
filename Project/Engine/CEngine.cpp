#include "pch.h"
#include "CEngine.h"

CEngine::CEngine()
	: m_hWnd(nullptr)
	, m_v2Resolution{}

{
}

CEngine::~CEngine()
{
	size_t size = m_vecObj.size();
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
	m_v2Resolution.x = static_cast<float>(_width);
	m_v2Resolution.y = static_cast<float>(_height);

	// Device, Context, SwapChain init
	CGraphics::GetInst()->Init(m_hWnd, m_v2Resolution.x, m_v2Resolution.y);

	// Manager init
	CTimeMgr::GetInst()->Init();
	CPathMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CAssetMgr::GetInst()->Init();
	CLevelMgr::GetInst()->Init();

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
	CLevelMgr::GetInst()->Tick();
}

void CEngine::Render()
{
	GRAPHICS->RenderBegin();

	// Rendering Pipeline
	{
		CLevelMgr::GetInst()->Render();
	}

	// Dear ImGui µÚ·Î ¿Å±è
	//GRAPHICS->RenderEnd();
}