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
	void AddObject(CGameObject* _obj, int _layerIdx);

public:
	void Begin();
	void Tick();
	void FinalTick();
	void Render();
};

