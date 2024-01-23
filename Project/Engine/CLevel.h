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
	CLayer* GetLayer(LAYER_TYPE _layerType) { return m_arrLayer[(UINT)_layerType]; }
	void AddObject(CGameObject* _obj, LAYER_TYPE _layerType);

public:
	void Begin();
	void Tick();
	void FinalTick();
	void Render();
};

