#include "pch.h"
#include "CLevelMgr.h"

CLevelMgr::CLevelMgr()
	: m_pCurLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_pCurLevel)
	{
		delete m_pCurLevel;
		m_pCurLevel = nullptr;
	}
}

void CLevelMgr::Tick()
{
	if (nullptr == m_pCurLevel)
		return;

	m_pCurLevel->Clear();
	m_pCurLevel->Tick();
	m_pCurLevel->FinalTick();
}

void CLevelMgr::FinalTick()
{
	m_pCurLevel->FinalTick();
}