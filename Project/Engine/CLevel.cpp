#include "pch.h"
#include "CLevel.h"

CLevel::CLevel()
	: m_arrLayer{}
{
	SetName(L"Level");

	// Level 에 속한 Layer 생성
	for (size_t i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i] = new CLayer((LAYER_TYPE)i);
	}

	GetLayer(LAYER_TYPE::DEFAULT)->SetName(L"DefaultLayer");
	GetLayer(LAYER_TYPE::BACKGROUND)->SetName(L"BackgroundLayer");
	GetLayer(LAYER_TYPE::PLAYER)->SetName(L"PlayerLayer");
	GetLayer(LAYER_TYPE::MONSTER)->SetName(L"MonsterLayer");
	GetLayer(LAYER_TYPE::LIGHT2D)->SetName(L"LightLayer");
	GetLayer(LAYER_TYPE::TILE)->SetName(L"TileLayer");
	GetLayer(LAYER_TYPE::UI)->SetName(L"UILayer");
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

CGameObject* CLevel::FindObjectByName(const wstring& _name)
{
	// Layer
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		// Parnet Obj
		const vector<CGameObject*>& vecParent = m_arrLayer[i]->GetLayerParents();

		for (size_t k =	0; k < vecParent.size(); ++k)
		{
			list<CGameObject*> list;
			list.push_back(vecParent[k]);

			while (!list.empty())
			{
				// Target
				CGameObject* obj = list.front();
				list.pop_front();

				// Child Obj
				const vector<CGameObject*> vecChildren = obj->GetChildren();
				for (size_t o = 0; o < vecChildren.size(); ++o)
					list.push_back(vecChildren[o]);

				// Result
				if (obj->GetName() == _name)
					return obj;
			}
		}
	}

	// Nothing
	return nullptr;
}

void CLevel::FindObjectByName(const wstring& _name, vector<CGameObject*>& _container)
{
	// Layer
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		// Parnet Obj
		const vector<CGameObject*>& vecParent = m_arrLayer[i]->GetLayerParents();

		for (size_t k = 0; k < vecParent.size(); ++k)
		{
			list<CGameObject*> list;
			list.push_back(vecParent[i]);

			while (!list.empty())
			{
				// Target
				CGameObject* obj = list.front();
				list.pop_front();

				// Child Obj
				const vector<CGameObject*> vecChildren = obj->GetChildren();
				for (CGameObject* child : vecChildren)
					list.push_back(child);

				// Result
				if (obj->GetName() == _name)
					_container.push_back(obj);
			}
		}
	}
}

void CLevel::Clear()
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->GetLayerObjects().clear();
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