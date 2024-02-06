#include "pch.h"
#include "CLayer.h"

CLayer::CLayer(LAYER_TYPE _type)
	: m_eLayerType(_type)
{
	SetName(L"UnknownLayer");
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

void CLayer::AddObject(CGameObject* _obj, bool _isChildMove)
{
	LAYER_TYPE eObjLayer = _obj->GetLayer();	// 인자로 들어온 객체가 속한 레이어
	CGameObject* pParent = _obj->GetParent();	// 인자로 들어온 객체의 부모객체

	// 부모 객체가 존재하지 않는 경우 (최상위 객체인 경우)
	if (nullptr == pParent)
	{
		// 이미 소속된 레이어가 존재하는 경우
		if (LAYER_TYPE::UNREGISTER != eObjLayer)
		{
			// 기존 소속 레이어의 m_vecParent 에서 제거
			_obj->DisconnectWithLayer();
		}

		// 새롭게 소속될 레이어의 m_vecParent에 등록
		m_vecParent.push_back(_obj);
	}

	// 인자로 들어온 객체와 자식 객체들의 레이어 소속 변경
	list<CGameObject*> que;
	que.push_back(_obj);

	while (!que.empty())
	{
		CGameObject* pObj = que.front();
		que.pop_front();

		// 객체의 레벨 소속여부 설정(특정 레벨에 소속됨)
		pObj->SetBelongLevel(true);

		vector<CGameObject*> children = pObj->GetChild();
		for (size_t i = 0; i < children.size(); ++i)
		{
			que.push_back(children[i]);
		}

		// 인자로 들어온 최초 입력 객체
		if (_obj == pObj)
		{
			// 최초 입력 객체는 무조건 해당 레이어 소속으로 설정
			pObj->SetLayer(m_eLayerType);
		}
		// 자식 객체들
		else
		{
			// 자식 객체도 부모를 따라가는 경우
			if (_isChildMove)
			{
				pObj->SetLayer(m_eLayerType);
			}
			// 자식 객체가 부모를 따라가지 않을 경우
			else
			{
				// 자식 객체가 부모를 따라가지 않더라도 소속된 레이어가 없다면 강제로 따라가게한다.
				if(LAYER_TYPE::UNREGISTER == pObj->GetLayer())
					pObj->SetLayer(m_eLayerType);
			}
		}
	}

}

void CLayer::RemoveObject(CGameObject* _obj)
{
	LAYER_TYPE eObjLayer = _obj->GetLayer();	// 인자로 들어온 객체가 속한 레이어
	CGameObject* pParent = _obj->GetParent();	// 인자로 들어온 객체의 부모객체

	// 객체가 속한 레이어가 없거나 해당 레이어에 속한 객체가 아닌 경우 함수 종료
	if (LAYER_TYPE::UNREGISTER == eObjLayer || m_eLayerType != eObjLayer)
	{
		MessageBoxA(nullptr, "Remove GameObject Failed", "Layer Error", MB_OK);
		return;
	}

	// 부모 객체가 존재하는 경우
	if (nullptr != pParent)
	{
		_obj->SetLayer(LAYER_TYPE::UNREGISTER);
	}
	// 부모 객체가 존재하지 않는 경우 (최상위 객체인 경우)
	else
	{
		// 소속 레이어의 m_vecParent 에서 해당 객체 제거
		vector<CGameObject*>::iterator iter = m_vecParent.begin();
		for (; iter != m_vecParent.end(); ++iter)
		{
			if (*iter == _obj)
			{
				m_vecParent.erase(iter);
				_obj->SetLayer(LAYER_TYPE::UNREGISTER);
				return;
			}
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
	vector<CGameObject*>::iterator iter = m_vecParent.begin();
	for (; iter != m_vecParent.end();)
	{
		CGameObject* pObj = *iter;
		pObj->FinalTick();

		// Parent 객체가 Dead 상태이면 m_vecParent 에서 제거한다.
		// m_vecParent에 들어있지 않다면 Parent 객체의 FinalTick()에 의해서 
		// Child 객체가 m_vecObject에 들어가는 과정이 사라지기에
		// Parent 객체뿐만아니라 Child 객체도 Render() 과정을 거치지 못한다.
		if (pObj->IsDead())
		{
			// Garbage Collector에 넣어줌
			M_GC->Add(pObj);
			iter = m_vecParent.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}