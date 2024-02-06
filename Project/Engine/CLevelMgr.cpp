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

	// ���� Level�� �� Layer�� m_vecObject �����̳ʸ� ���
	m_pCurLevel->Clear();		
	// ���� Level�� �� Layer�� m_vecParent �����̳��� ��ü���� Tick() ȣ��
	// GameObject�� Component, ChildObj �� Tick() ȣ��
	m_pCurLevel->Begin();
	m_pCurLevel->Tick();	
	// ���� Level�� �� Layer�� m_vecParent �����̳��� ��ü���� FinalTick() ȣ��
	// FinalTick() ȣ�� �� Dead ���°� �Ǹ� m_vecParent �����̳ʿ��� ������, GC�� �߰��ȴ�.
	// �θ�ü�� m_vecParent�� �������������, �ڽİ�ü�� ���������ӿ� �Բ� Render������ ��ġ�� ���Ѵ�.
	m_pCurLevel->FinalTick();
}