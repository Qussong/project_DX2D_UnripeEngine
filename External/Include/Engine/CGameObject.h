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
	// BasicComp  : ������ ������ ���� -> �迭(arr)
	// RenderComp : ��ü���� �� �ϳ��� ����
	// Script	  : ��� �������� �����Ұ� -> ����(vec)
	CComponent*				m_arrBasicComp[(uint32)COMPONENT_TYPE::BASIC_END];
	CRenderComponent*		m_pRenderComp;
	vector<CScript*>		m_vecScript;

	// �������� (Parent, Child)
	CGameObject*			m_pParent;		// �ش� GameObject�� �Ҽӵ� �θ�ü(nullptr �̸� �θ�ü ����)
	vector<CGameObject*>	m_vecChild;		// �����ϰ� �ִ� �ڽİ�ü
	LAYER_TYPE				m_eLayerType;	// �Ҽӵ� Layer Index
	bool					m_bDead;		// �ش� �÷��� ���� ������� TaskMgr ���� ��ü ����

public:
	// Getter
	CGameObject*			GetParent() { return m_pParent; }
	bool					IsDead() { return m_bDead; }
	vector<CGameObject*>&	GetChild() { return m_vecChild; }
	LAYER_TYPE				GetLayer() { return m_eLayerType; }

	// Setter
	void					SetParent(CGameObject* _obj) { m_pParent = _obj; }
	void					SetDead(bool _flag) { m_bDead = _flag; }
	void					AddChild(CGameObject* _child);	// �ڽ� ��ü �߰�
	void					SetLayer(LAYER_TYPE _type) { m_eLayerType = _type; }

public:
	void			AddComponent(CComponent* _comp);
	//CComponent*	GetComponent(COMPONENT_TYPE _type) { return m_arrBasicComp[(uint32)_type]; }	// ��� �ɰ� ���Ƽ� �ӽ� �ּ�
	CTransform*		Transform() { return static_cast<CTransform*>(m_arrBasicComp[(uint32)COMPONENT_TYPE::TRANSFORM]); }
	CMeshRender*	MeshRender();
	CCamera*		Camera() { return static_cast<CCamera*>(m_arrBasicComp[(uint32)COMPONENT_TYPE::CAMERA]); }
	CCollider2D*	Collider2D() { return static_cast<CCollider2D*>(m_arrBasicComp[(uint32)COMPONENT_TYPE::COLLIDER2D]); }
	CAnimator2D*	Animator2D() { return static_cast<CAnimator2D*>(m_arrBasicComp[(uint32)COMPONENT_TYPE::ANIMATOR2D]); }
	CLight2D*		Light2D() { return static_cast<CLight2D*>(m_arrBasicComp[(uint32)COMPONENT_TYPE::LIGHT2D]); }

public:
	void DisconnectWithParent();	// �θ� ��ü�κ��� ����
	void DisconnectWithLayer();		// �Ҽ� ���̾�� ����
	void Destroy();					// �ڱ��ڽ� ����

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
