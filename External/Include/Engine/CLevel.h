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
	void Clear();	// 이전 프레임에 레이어의 m_vecObject에 적제된 객체들 클리어

public:
	CLayer* GetLayer(LAYER_TYPE _layerType);
	CLayer* GetLayer(const wstring& _layerName);

public:
	void Begin();
	void Tick();
	void FinalTick();
	void Render();
};

