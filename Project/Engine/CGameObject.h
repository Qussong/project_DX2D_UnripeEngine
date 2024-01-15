#pragma once
#include "CEntity.h"

class CComponent;
class CRenderComponent;
class CTransform;
class CMeshRender;

class CGameObject
	: public CEntity
{
	using Super = CEntity;

public:
	CGameObject();
	virtual ~CGameObject();

private:
	/*
	* BasicComp : 개수가 정해져 있기에 arr
	* RenderComp : 객체마다 단 하나만 존재할수있다.
	* Script : 몇개가 존재할지 예측불가하기에 vec
	*/
	CComponent*			m_arrBasicComp[(uint32)COMPONENT_TYPE::END];
	CRenderComponent*	m_pRenderComp;
	vector<CScript*>	m_vecScript;

public:
	void Begin();
	void Tick();
	void FinalTick();
	void Render();

public:
	void AddComponent(CComponent* _comp);
	CComponent* GetComponent(COMPONENT_TYPE _type) { return m_arrBasicComp[(uint32)_type]; }

	CTransform* Transform() { return (CTransform*)m_arrBasicComp[(uint32)COMPONENT_TYPE::TRANSFORM]; }
	CMeshRender* MeshRender();
};