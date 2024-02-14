#pragma once

class CComponentUI
	: public CUI
{
	using Super = CUI;

public:
	CComponentUI(const string& _name, const string& _id, COMPONENT_TYPE _type);
	virtual ~CComponentUI();

private:
	CGameObject*	m_pTargetObj;
	COMPONENT_TYPE	m_eType;
	string			m_strCompTitle;	// name,title

public:
	// Getter
	CGameObject* GetTargetObj() { return m_pTargetObj; }
	const COMPONENT_TYPE GetType() { return m_eType; }

	// Setter
	void SetTargetObj(CGameObject* _obj);
	void SetType(COMPONENT_TYPE _type) { m_eType = _type; }

public:
	virtual void Tick() override {}
	virtual void SetWindowOption() override {}	// UI芒 可记 技泼
	virtual void Render_Update() override;		// UI芒 备己 技泼
};

