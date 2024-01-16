#include "pch.h"
#include "CLayer.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
	uint32 size = m_vecParent.size();
	for (size_t i = 0; i < size; ++i)
	{
		delete m_vecParent[i];
		m_vecParent[i] = nullptr;
	}
}

void CLayer::Begin()
{
	uint32 size = m_vecParent.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecParent[i]->Begin();
	}
}

void CLayer::Tick()
{
	uint32 size = m_vecParent.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecParent[i]->Tick();
	}
}

void CLayer::FinalTick()
{
	uint32 size = m_vecParent.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecParent[i]->FinalTick();
	}
}

void CLayer::Render()
{
	uint32 size = m_vecParent.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecParent[i]->Render();
	}
}
