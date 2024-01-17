#include "pch.h"
#include "CLayer.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
	size_t size = m_vecParent.size();
	for (size_t i = 0; i < size; ++i)
	{
		delete m_vecParent[i];
		m_vecParent[i] = nullptr;
	}
}

void CLayer::Begin()
{
	size_t size = m_vecParent.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecParent[i]->Begin();
	}
}

void CLayer::Tick()
{
	size_t size = m_vecParent.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecParent[i]->Tick();
	}
}

void CLayer::FinalTick()
{
	size_t size = m_vecParent.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecParent[i]->FinalTick();
	}
}

void CLayer::Render()
{
	size_t size = m_vecParent.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecParent[i]->Render();
	}
}
