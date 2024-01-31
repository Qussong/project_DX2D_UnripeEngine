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
	size_t layerCnt = LAYER_MAX;
	for (size_t i = 0; i < layerCnt; i++)
	{
		delete m_arrLayer[i];
		m_arrLayer[i] = nullptr;
	}
}

CLayer* CLevel::GetLayer(LAYER_TYPE _layerType)
{
	if (LAYER_TYPE::UNREGISTER == _layerType)
	{
		MessageBoxA(nullptr, "Call the Invalid Layer.\n(LAYER_TYPE::UNREGISTER) ", "Call Error", MB_OK);
		return nullptr;
	}

	return m_arrLayer[(UINT)_layerType];
}

CLayer* CLevel::GetLayer(const wstring& _layerName)
{
	for (size_t i = 0; i < LAYER_MAX; ++i)
	{
		const wstring strLayerName = m_arrLayer[i]->GetName();
		if (_layerName == strLayerName)
		{
			return m_arrLayer[i];
		}
	}

	MessageBoxA(nullptr, "Search Invalid Layer", "Layer Error", MB_OK);
	return nullptr;
}

void CLevel::Clear()
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->GetLayerObject().clear();
	}
}

void CLevel::AddObject(CGameObject* _obj, LAYER_TYPE _layerType, bool _isChildMove)
{
	m_arrLayer[(UINT)_layerType]->AddObject(_obj, _isChildMove);
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
