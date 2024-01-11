#include "pch.h"
#include "CEngine.h"

#include "CGraphics.h"

CEngine::CEngine()
	: m_hWnd(nullptr)
	, m_width(0)
	, m_height(0)

{
}

CEngine::~CEngine()
{
}

int CEngine::Init(HWND _hWnd, uint32 _width, uint32 _height)
{
	m_hWnd = _hWnd;
	m_width = _width;
	m_height = _height;
	
	// Device, Context, SwapChain 초기화
	CGraphics::GetInst()->Init(m_hWnd, m_width, m_height);

	// Manager 초기화
	CTimeMgr::GetInst()->Init();
	CPathMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();

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
}

void CEngine::Render()
{
	CGraphics::GetInst()->RenderBegin();

	// Rendering Pipeline
	{

	}

	CGraphics::GetInst()->RenderEnd();
}