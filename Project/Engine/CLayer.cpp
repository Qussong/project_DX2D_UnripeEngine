#include "pch.h"
#include "CLayer.h"

CLayer::CLayer(LAYER_TYPE _type)
	: m_eLayerType(_type)
{
	switch (_type)
	{
	case LAYER_TYPE::LAYER_0:
		SetName(L"LAYER_0");
		break;
	case LAYER_TYPE::LAYER_1:
		SetName(L"LAYER_1");
		break;
	case LAYER_TYPE::LAYER_2:
		SetName(L"LAYER_2");
		break;
	case LAYER_TYPE::LAYER_3:
		SetName(L"LAYER_3");
		break;
	default:
		SetName(L"DefaultLayer");
		break;
	}
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

void CLayer::RegisterObject(CGameObject* _obj)
{
	if (nullptr == _obj->GetParent())
	{
		m_vecParent.push_back(_obj);
	}
	m_vecObject.push_back(_obj);

	_obj->SetLayer(m_eLayerType);

	// 자식 객체 존재 여부 확인
	CheckChildAndChangeLayer(_obj, ADD_DEL_FLAG::ADD, m_eLayerType);
}

void CLayer::RemoveObject(CGameObject* _obj)
{
	LAYER_TYPE eLayer = _obj->GetLayer();
	CGameObject* pParent = _obj->GetParent();

	// 객체가 속한 layer가 없거나 해당 레이어에 속한 객체가 아닌 경우
	if (LAYER_TYPE::NONE == eLayer || m_eLayerType != eLayer)
	{
		MessageBoxA(nullptr, "Remove GameObject Failed", "Layer Error", MB_OK);
		_exit(EXIT_FAILURE);
	}

	// 최상위 객체인 경우
	// 해당 레이어의 m_vecParent에서 해당 객체 제거
	if (nullptr == pParent)
	{
		EraseFromGroup(_obj, m_vecParent);
	}

	// 해당 레이어의 m_vecObject에서 해당 객체 제거
	EraseFromGroup(_obj, m_vecObject);
	// 자식 객체 존재여부 확인 및 자식 객체의 레이어 변경
	CheckChildAndChangeLayer(_obj);
	// 레이어 변경
	_obj->SetLayer(LAYER_TYPE::NONE);
}

void CLayer::EraseFromGroup(CGameObject* _target, vector<CGameObject*> _group)
{
	vector<CGameObject*>::iterator iter = _group.begin();
	for (; iter != _group.end(); ++iter)
	{
		if (*iter == _target)
		{
			_group.erase(iter);
			return;
		}
	}
}

void CLayer::DoubleCheck(CGameObject* _obj)
{
	// 이미 vec안에 해당 객체가 존재하는지 확인하는 함수 구현하기
}

void CLayer::CheckChildAndChangeLayer(CGameObject* _obj, ADD_DEL_FLAG _flag, LAYER_TYPE _layerType)
{
	// 자식 객체 존재여부 확인
	vector<CGameObject*> vecChild = _obj->GetChild();
	size_t childCnt = vecChild.size();

	// 자식 객체가 존재하지 않는 경우
	if (childCnt < 0)
	{
		// 함수 종료
		return;
	}
	// 자식 객체가 존재하는 경우
	else
	{
		for (size_t i = 0; i < childCnt; ++i)
		{
			// 특정 레이어에 추가하는 작업인 경우
			if (ADD_DEL_FLAG::ADD == _flag)
			{
				m_vecObject.push_back(vecChild[i]);
			}
			// 특정 레이어로부터 제거하는 작업인 경우
			else
			{
				EraseFromGroup(vecChild[i], m_vecObject);
			}
			vecChild[i]->SetLayer(_layerType);

			// 손자 존재여부 확인
			CheckChildAndChangeLayer(vecChild[i], _flag, _layerType);
		}
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
	size_t size = m_vecObject.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecObject[i]->Render();
	}
}
