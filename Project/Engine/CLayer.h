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
	void RegisterObject(CGameObject* _obj); // 해당 레이어에 특정 객체 추가
	void RemoveObject(CGameObject* _obj);	// 해당 레이어에서 특정 객체 제거

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

