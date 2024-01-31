#pragma once

class CLayer
	: public CEntity
{
	using Super = CEntity;

public:
	CLayer(LAYER_TYPE _type);
	virtual ~CLayer();

private:
	LAYER_TYPE				m_eLayerType;	// 해당 레이어의 타입 (레이어 구분 기준)
	vector<CGameObject*>	m_vecParent;	// 해당 레이어에 속한 부모객체만 저장
	vector<CGameObject*>	m_vecObject;	// 해당 레이어에 속한 모든객체 저장

public:
	void AddObject(CGameObject* _obj, bool _isChildMove);	// 인자로 들어온 객체 해당 레이어에 추가
	void RemoveObject(CGameObject* _obj);					// 인자로 들어온 객체 해당 레이어에서 제거
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

