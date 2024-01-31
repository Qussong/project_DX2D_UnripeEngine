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

	// test
	Test();
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

void CLevelMgr::Test()
{
	if (KEY_STATE::TAP == M_KEY->GetKeyState(KEY::C))
	{
		LAYER_TYPE type = m_pTestObj->GetLayer();
		CLayer* layer = m_pCurLevel->GetLayer(type);
		layer->RemoveObject(m_pTestObj);
	}

	if (KEY_STATE::TAP == M_KEY->GetKeyState(KEY::V))
	{
		LAYER_TYPE type = LAYER_TYPE::LAYER_1;
		CLayer* layer = m_pCurLevel->GetLayer(type);
		layer->AddObject(m_pTestObj, true);	// 자식객체도 부모객체의 레이어 따라감
	}
}
