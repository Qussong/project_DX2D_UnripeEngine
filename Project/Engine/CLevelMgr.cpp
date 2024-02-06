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

	// 현재 Level의 각 Layer의 m_vecObject 컨테이너를 비움
	m_pCurLevel->Clear();		
	// 현재 Level의 각 Layer의 m_vecParent 컨테이너의 객체들의 Tick() 호출
	// GameObject의 Component, ChildObj 의 Tick() 호출
	m_pCurLevel->Begin();
	m_pCurLevel->Tick();	
	// 현재 Level의 각 Layer의 m_vecParent 컨테이너의 객체들의 FinalTick() 호출
	// FinalTick() 호출 후 Dead 상태가 되면 m_vecParent 컨테이너에서 빠지고, GC에 추가된다.
	// 부모객체가 m_vecParent에 들어있지않으면, 자식객체도 다음프레임에 함께 Render과정을 거치지 못한다.
	m_pCurLevel->FinalTick();
}