#include "pch.h"
#include "CLevel.h"

CLevel::CLevel()
	: m_arrLayer{}
{
	// Level 에 속한 Layer 생성
	for (size_t i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i] = new CLayer((LAYER_TYPE)i);
	}
}

CLevel::~CLevel()
{
	for (size_t i = 0; i < LAYER_MAX; i++)
	{
		delete m_arrLayer[i];
		m_arrLayer[i] = nullptr;
	}
}

void CLevel::AddObject(CGameObject* _obj, LAYER_TYPE _layerType)
{
	m_arrLayer[(UINT)_layerType]->RegisterObject(_obj);
}

void CLevel::Begin()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->Begin();
	}
}

void CLevel::Tick()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->Tick();
	}
}

void CLevel::FinalTick()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->FinalTick();
	}
}

void CLevel::Render()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->Render();
	}
}
