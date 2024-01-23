#pragma once
#include "CEntity.h"

class CComponent;
class CRenderComponent;
class CTransform;
class CMeshRender;
class CCamera;

class CGameObject
	: public CEntity
{
	using Super = CEntity;

public:
	CGameObject();
	virtual ~CGameObject();

private:
	// BasicComp  : ������ ������ ���� -> �迭(arr)
	// RenderComp : ��ü���� �� �ϳ��� ����
	// Script	  : ��� �������� �����Ұ� -> ����(vec)
	CComponent*				m_arrBasicComp[(uint32)COMPONENT_TYPE::BASIC_END];
	CRenderComponent*		m_pRenderComp;
	vector<CScript*>		m_vecScript;

	// �������� (Parent, Child)
	CGameObject*			m_pParent;	// �ش� GameObject�� �Ҽӵ� �θ�ü(nullptr �̸� �θ�ü ����)
	vector<CGameObject*>	m_vecChild;	// �����ϰ� �ִ� �ڽİ�ü

	LAYER_TYPE				m_eLayerIdx;	// �Ҽӵ� Layer Index

public:
	void Begin();
	void Tick();
	void FinalTick();
	void Render();

public:
	void AddComponent(CComponent* _comp);
	//CComponent* GetComponent(COMPONENT_TYPE _type) { return m_arrBasicComp[(uint32)_type]; }	// ��� �ɰ� ���Ƽ� �ӽ� �ּ�

	CTransform*		Transform() { return static_cast<CTransform*>(m_arrBasicComp[(uint32)COMPONENT_TYPE::TRANSFORM]); }
	CMeshRender*	MeshRender();
	CCamera*		Camera() { return static_cast<CCamera*>(m_arrBasicComp[(uint32)COMPONENT_TYPE::CAMERA]); }

public:
	CGameObject* GetParent() { return m_pParent; }			// �θ�ü Getter
	void SetParent(CGameObject* _obj) { m_pParent = _obj; }	// �θ�ü Setter

	void Independent();								// �θ� ��ü�κ��� ����

	void AddChild(CGameObject* _child);				// �ڽ� ��ü �߰�

	vector<CGameObject*> GetChild() { return m_vecChild; }

public:
	LAYER_TYPE	GetLayer() { return m_eLayerIdx; }
	void		SetLayer(LAYER_TYPE _type) { m_eLayerIdx = _type; }
};