#pragma once

class CLayer;

class CLevel
	: public CEntity
{
	using Super = CEntity;

public:
	CLevel();
	virtual ~CLevel();

private:
	CLayer* m_arrLayer[LAYER_MAX];

public:
	void AddObject(CGameObject* _obj, LAYER_TYPE _layerType, bool _isChildMove = false);
	void Clear();	// ���� �����ӿ� ���̾��� m_vecObject�� ������ ��ü�� Ŭ����

	CLayer* GetLayer(LAYER_TYPE _layerType);
	CLayer* GetLayer(const wstring& _layerName);

	CGameObject* FindObjectByName(const wstring& _name);
	void		 FindObjectByName(const wstring& _name, vector<CGameObject*>& _container);

public:
	void Begin();
	void Tick();
	void FinalTick();
};

