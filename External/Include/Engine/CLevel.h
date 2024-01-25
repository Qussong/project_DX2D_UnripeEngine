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
	CLayer* GetLayer(LAYER_TYPE _layerType);
	void AddObject(CGameObject* _obj, LAYER_TYPE _layerType, bool _isChildMove = false);

	void Clear();	// ���� �����ӿ� ���̾��� m_vecObject�� ������ ��ü�� Ŭ����

public:
	void Begin();
	void Tick();
	void FinalTick();
	void Render();
};

