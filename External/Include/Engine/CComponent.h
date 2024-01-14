#pragma once
#include "CEntity.h"

class CComponent
	: public CEntity
{
	using Super = CEntity;

public:
	CComponent(COMPONENT_TYPE _type);
	virtual ~CComponent();
	
private:
	const COMPONENT_TYPE	m_eType;
	CGameObject*			m_pOwner;

public:
	virtual void Begin() = 0;
	virtual void Tick() = 0;
	virtual void FinalTick() = 0;
	virtual void UpdateData() = 0;

public:
	COMPONENT_TYPE GetType() { return m_eType; }
	CGameObject* GetOwner() { return m_pOwner; }

	void SetOwner(CGameObject* _owner) { m_pOwner = _owner; }

};

