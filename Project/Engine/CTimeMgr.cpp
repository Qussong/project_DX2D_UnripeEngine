#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr()
	: m_lFrequency{}
	, m_lPrevCnt{}
	, m_lCurCnt{}
	, m_fDeltaTime(0.f)
	, m_fAccTime(0.f)
	, m_iFrameCnt(0)
	, m_iFPS(0)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Init()
{
	QueryPerformanceFrequency(&m_lFrequency);
	QueryPerformanceCounter(&m_lPrevCnt);
}

void CTimeMgr::Tick()
{
	QueryPerformanceCounter(&m_lCurCnt);

	m_fDeltaTime = float(m_lCurCnt.QuadPart - m_lPrevCnt.QuadPart) / float(m_lFrequency.QuadPart);

	m_lPrevCnt = m_lCurCnt;

	// DeltaTime 보정 (최소 FPS 60)
	if ((1.f / 60.f) < m_fDeltaTime)
		m_fDeltaTime = 1.f / 60.f;

	m_fAccTime += m_fDeltaTime;

	// 1초마다 FPS 출력 및 갱신
	if (1.f <= m_fAccTime)
	{
		// PrintFPS();

		m_iFPS = m_iFrameCnt;
		m_fAccTime = 0.f;
		m_iFrameCnt = 0;
	}
	++m_iFrameCnt;
}

void CTimeMgr::PrintFPS()
{
	wchar_t text[50] = {};
	swprintf_s(text, sizeof(text) / sizeof(wchar_t), L"DT : %f, FPS : %d", m_fDeltaTime, m_iFPS);
	SetWindowText(CEngine::GetInst()->GetWindowHandle(), text);
}
