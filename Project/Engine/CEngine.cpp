#include "pch.h"
#include "CEngine.h"

#include "CGraphics.h"

CEngine::CEngine()
	: m_hWnd(nullptr)

{
}

CEngine::~CEngine()
{
}

int CEngine::Init(HWND _hWnd)
{
	m_hWnd = _hWnd;

	CGraphics::GetInst()->Init(m_hWnd, WINDOW_WIDTH, WINDOW_HEIGHT);

	return S_OK;
}

void CEngine::Update()
{
}

void CEngine::Render()
{
	CGraphics::GetInst()->RenderBegin();

	// Rendering Pipeline
	{

	}

	CGraphics::GetInst()->RenderEnd();
}