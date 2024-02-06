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
	LAYER_TYPE eObjLayer = _obj->GetLayer();	// ���ڷ� ���� ��ü�� ���� ���̾�
	CGameObject* pParent = _obj->GetParent();	// ���ڷ� ���� ��ü�� �θ�ü

	// �θ� ��ü�� �������� �ʴ� ��� (�ֻ��� ��ü�� ���)
	if (nullptr == pParent)
	{
		// �̹� �Ҽӵ� ���̾ �����ϴ� ���
		if (LAYER_TYPE::UNREGISTER != eObjLayer)
		{
			// ���� �Ҽ� ���̾��� m_vecParent ���� ����
			_obj->DisconnectWithLayer();
		}

		// ���Ӱ� �Ҽӵ� ���̾��� m_vecParent�� ���
		m_vecParent.push_back(_obj);
	}

	// ���ڷ� ���� ��ü�� �ڽ� ��ü���� ���̾� �Ҽ� ����
	list<CGameObject*> que;
	que.push_back(_obj);

	while (!que.empty())
	{
		CGameObject* pObj = que.front();
		que.pop_front();

		// ��ü�� ���� �Ҽӿ��� ����(Ư�� ������ �Ҽӵ�)
		pObj->SetBelongLevel(true);

		vector<CGameObject*> children = pObj->GetChild();
		for (size_t i = 0; i < children.size(); ++i)
		{
			que.push_back(children[i]);
		}

		// ���ڷ� ���� ���� �Է� ��ü
		if (_obj == pObj)
		{
			// ���� �Է� ��ü�� ������ �ش� ���̾� �Ҽ����� ����
			pObj->SetLayer(m_eLayerType);
		}
		// �ڽ� ��ü��
		else
		{
			// �ڽ� ��ü�� �θ� ���󰡴� ���
			if (_isChildMove)
			{
				pObj->SetLayer(m_eLayerType);
			}
			// �ڽ� ��ü�� �θ� ������ ���� ���
			else
			{
				// �ڽ� ��ü�� �θ� ������ �ʴ��� �Ҽӵ� ���̾ ���ٸ� ������ ���󰡰��Ѵ�.
				if(LAYER_TYPE::UNREGISTER == pObj->GetLayer())
					pObj->SetLayer(m_eLayerType);
			}
		}
	}

}

void CLayer::RemoveObject(CGameObject* _obj)
{
	LAYER_TYPE eObjLayer = _obj->GetLayer();	// ���ڷ� ���� ��ü�� ���� ���̾�
	CGameObject* pParent = _obj->GetParent();	// ���ڷ� ���� ��ü�� �θ�ü

	// ��ü�� ���� ���̾ ���ų� �ش� ���̾ ���� ��ü�� �ƴ� ��� �Լ� ����
	if (LAYER_TYPE::UNREGISTER == eObjLayer || m_eLayerType != eObjLayer)
	{
		MessageBoxA(nullptr, "Remove GameObject Failed", "Layer Error", MB_OK);
		return;
	}

	// �θ� ��ü�� �����ϴ� ���
	if (nullptr != pParent)
	{
		_obj->SetLayer(LAYER_TYPE::UNREGISTER);
	}
	// �θ� ��ü�� �������� �ʴ� ��� (�ֻ��� ��ü�� ���)
	else
	{
		// �Ҽ� ���̾��� m_vecParent ���� �ش� ��ü ����
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

		// Parent ��ü�� Dead �����̸� m_vecParent ���� �����Ѵ�.
		// m_vecParent�� ������� �ʴٸ� Parent ��ü�� FinalTick()�� ���ؼ� 
		// Child ��ü�� m_vecObject�� ���� ������ ������⿡
		// Parent ��ü�Ӹ��ƴ϶� Child ��ü�� Render() ������ ��ġ�� ���Ѵ�.
		if (pObj->IsDead())
		{
			// Garbage Collector�� �־���
			M_GC->Add(pObj);
			iter = m_vecParent.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}