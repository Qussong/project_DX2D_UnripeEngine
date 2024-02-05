#pragma once
#include "CEntity.h"

class CComponent;
class CRenderComponent;
class CTransform;
class CMeshRender;
class CCamera;
class Collider2D;
class CAnimator2D;

class CGameObject
	: public CEntity
{
	using Super = CEntity;

public:
	CGameObject();
	virtual ~CGameObject();

private:
	// BasicComp  : 개수가 정해져 있음 -> 배열(arr)
	// RenderComp : 객체마다 단 하나만 존재
	// Script	  : 몇개가 존재할지 예측불가 -> 벡터(vec)
	CComponent*				m_arrBasicComp[(uint32)COMPONENT_TYPE::BASIC_END];
	CRenderComponent*		m_pRenderComp;
	vector<CScript*>		m_vecScript;

	// 계층구조 (Parent, Child)
	CGameObject*			m_pParent;		// 해당 GameObject가 소속된 부모객체(nullptr 이면 부모객체 없음)
	vector<CGameObject*>	m_vecChild;		// 소유하고 있는 자식객체
	LAYER_TYPE				m_eLayerType;	// 소속된 Layer Index
	bool					m_bDead;		// 해당 플래그 값을 기반으로 TaskMgr 에서 객체 관리

public:
	// Getter
	CGameObject*			GetParent() { return m_pParent; }
	bool					IsDead() { return m_bDead; }
	vector<CGameObject*>&	GetChild() { return m_vecChild; }
	LAYER_TYPE				GetLayer() { return m_eLayerType; }

	// Setter
	void					SetParent(CGameObject* _obj) { m_pParent = _obj; }
	void					SetDead(bool _flag) { m_bDead = _flag; }
	void					AddChild(CGameObject* _child);	// 자식 객체 추가
	void					SetLayer(LAYER_TYPE _type) { m_eLayerType = _type; }

public:
	void			AddComponent(CComponent* _comp);
	//CComponent*	GetComponent(COMPONENT_TYPE _type) { return m_arrBasicComp[(uint32)_type]; }	// 없어도 될것 같아서 임시 주석
	CTransform*		Transform() { return static_cast<CTransform*>(m_arrBasicComp[(uint32)COMPONENT_TYPE::TRANSFORM]); }
	CMeshRender*	MeshRender();
	CCamera*		Camera() { return static_cast<CCamera*>(m_arrBasicComp[(uint32)COMPONENT_TYPE::CAMERA]); }
	CCollider2D*	Collider2D() { return static_cast<CCollider2D*>(m_arrBasicComp[(uint32)COMPONENT_TYPE::COLLIDER2D]); }
	CAnimator2D*	Animator2D() { return static_cast<CAnimator2D*>(m_arrBasicComp[(uint32)COMPONENT_TYPE::ANIMATOR2D]); }
	CLight2D*		Light2D() { return static_cast<CLight2D*>(m_arrBasicComp[(uint32)COMPONENT_TYPE::LIGHT2D]); }

public:
	void DisconnectWithParent();	// 부모 객체로부터 독립
	void DisconnectWithLayer();		// 소속 레이어에서 독립
	void Destroy();					// 자기자신 제거

public:
	const vector<CScript*>& GetScripts() { return m_vecScript; }
	template <typename T>
	T* GetScript();

public:
	void Begin();
	void Tick();
	void FinalTick();
	void Render();
};

template<typename T>
inline T* CGameObject::GetScript()
{
	size_t iScriptCnt = m_vecScript.size();
	for (size_t i = 0; i < iScriptCnt; ++i)
	{
		if (dynamic_cast<T*>(m_vecScript[i]))
			return static_cast<T*>(m_vecScript[i]);
	}

	return nullptr;
}
