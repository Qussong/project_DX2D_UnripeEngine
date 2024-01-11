#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr()
	: m_frequency{}
	, m_prevCnt{}
	, m_curCnt{}
	, m_deltaTime(0.f)
	, m_fAccTime(0.f)
	, m_FPS(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_prevCnt);
}

void CTimeMgr::Tick()
{
	QueryPerformanceCounter(&m_curCnt);

	m_deltaTime = float(m_curCnt.QuadPart - m_prevCnt.QuadPart) / float(m_frequency.QuadPart);

	m_prevCnt = m_curCnt;

	// DeltaTime 보정 (최소 FPS 60)
	if ((1.f / 60.f) < m_deltaTime)
		m_deltaTime = 1.f / 60.f;

	m_fAccTime += m_deltaTime;

	// 1초마다 FPS 출력 갱신
	if (1.f <= m_fAccTime)
	{
		wchar_t text[50] = {};
		swprintf_s(text, sizeof(text) / sizeof(wchar_t), L"DT : %f, FPS : %d", m_deltaTime, m_FPS);
		SetWindowText(CEngine::GetInst()->GetWindowHandle(), text);

		m_fAccTime = 0.f;
		m_FPS = 0;
	}
	++m_FPS;
}

