#pragma once

class CLayer
	: public CEntity
{
	using Super = CEntity;

public:
	CLayer(LAYER_TYPE _type);
	virtual ~CLayer();

private:
	LAYER_TYPE				m_eLayerType;	// �ش� ���̾��� Ÿ�� (���̾� ���� ����)

	vector<CGameObject*>	m_vecParent;	// �ش� ���̾ ���� �θ�ü�� ����
	vector<CGameObject*>	m_vecObject;	// �ش� ���̾ ���� ��簴ü ����

public:
	void RegisterObject(CGameObject* _obj); // �ش� ���̾ Ư�� ��ü �߰�
	void RemoveObject(CGameObject* _obj);	// �ش� ���̾�� Ư�� ��ü ����

private:
	void EraseFromGroup(CGameObject* _target, vector<CGameObject*> _group);

	void CheckChildAndChangeLayer(CGameObject* _obj,
								ADD_DEL_FLAG _flag = ADD_DEL_FLAG::DEL,
								LAYER_TYPE _layerType = LAYER_TYPE::NONE);

public:
	void Begin();
	void Tick();
	void FinalTick();
	void Render();
};

