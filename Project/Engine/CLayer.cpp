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

	// �ڽ� ��ü ���� ���� Ȯ��
	CheckChildAndChangeLayer(_obj, ADD_DEL_FLAG::ADD, m_eLayerType);
}

void CLayer::RemoveObject(CGameObject* _obj)
{
	LAYER_TYPE eLayer = _obj->GetLayer();
	CGameObject* pParent = _obj->GetParent();

	// ��ü�� ���� layer�� ���ų� �ش� ���̾ ���� ��ü�� �ƴ� ���
	if (LAYER_TYPE::NONE == eLayer || m_eLayerType != eLayer)
	{
		MessageBoxA(nullptr, "Remove GameObject Failed", "Layer Error", MB_OK);
		_exit(EXIT_FAILURE);
	}

	// �ֻ��� ��ü�� ���
	// �ش� ���̾��� m_vecParent���� �ش� ��ü ����
	if (nullptr == pParent)
	{
		EraseFromGroup(_obj, m_vecParent);
	}

	// �ش� ���̾��� m_vecObject���� �ش� ��ü ����
	EraseFromGroup(_obj, m_vecObject);
	// �ڽ� ��ü ���翩�� Ȯ�� �� �ڽ� ��ü�� ���̾� ����
	CheckChildAndChangeLayer(_obj);
	// ���̾� ����
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
	// �̹� vec�ȿ� �ش� ��ü�� �����ϴ��� Ȯ���ϴ� �Լ� �����ϱ�
}

void CLayer::CheckChildAndChangeLayer(CGameObject* _obj, ADD_DEL_FLAG _flag, LAYER_TYPE _layerType)
{
	// �ڽ� ��ü ���翩�� Ȯ��
	vector<CGameObject*> vecChild = _obj->GetChild();
	size_t childCnt = vecChild.size();

	// �ڽ� ��ü�� �������� �ʴ� ���
	if (childCnt < 0)
	{
		// �Լ� ����
		return;
	}
	// �ڽ� ��ü�� �����ϴ� ���
	else
	{
		for (size_t i = 0; i < childCnt; ++i)
		{
			// Ư�� ���̾ �߰��ϴ� �۾��� ���
			if (ADD_DEL_FLAG::ADD == _flag)
			{
				m_vecObject.push_back(vecChild[i]);
			}
			// Ư�� ���̾�κ��� �����ϴ� �۾��� ���
			else
			{
				EraseFromGroup(vecChild[i], m_vecObject);
			}
			vecChild[i]->SetLayer(_layerType);

			// ���� ���翩�� Ȯ��
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
