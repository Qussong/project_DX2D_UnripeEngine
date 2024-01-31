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
	void AddObject(CGameObject* _obj, bool _isChildMove);	// ���ڷ� ���� ��ü �ش� ���̾ �߰�
	void RemoveObject(CGameObject* _obj);					// ���ڷ� ���� ��ü �ش� ���̾�� ����
	void RegisterObject(CGameObject* _obj) { m_vecObject.push_back(_obj); }

public:
	// Getter
	LAYER_TYPE					GetLayerType() { return m_eLayerType; }
	vector<CGameObject*>&		GetLayerObjects() { return m_vecObject; }

public:
	void Begin();
	void Tick();
	void FinalTick();
};

