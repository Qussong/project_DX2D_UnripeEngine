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
	* BasicComp : ������ ������ �ֱ⿡ arr
	* RenderComp : ��ü���� �� �ϳ��� �����Ҽ��ִ�.
	* Script : ��� �������� �����Ұ��ϱ⿡ vec
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