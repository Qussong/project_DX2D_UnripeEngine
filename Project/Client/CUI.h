#pragma once

class CUI
{
public:
	CUI(const string& _strName, const string& _strID);
	virtual ~CUI();

private:
	string				m_strName;		// �̸�
	string				m_strID;		// ##�̸�
	bool				m_bActive;		// UIâ�� Ȱ��ȭ ����
	ImVec2				m_v2Size;		// ?

	ImGuiWindowFlags	m_eWindowFlags;	// UIâ�� ���� flag �� (ImGui) -> Parent��ü�� ��쿡�� ��ȿ��

	CUI*				m_pParent;
	vector<CUI*>		m_vecChildren;

public:
	// Getter
	const string&	GetName()	{ return m_strName; }
	const string&	GetID()		{ return m_strID; }
	const bool		IsActive()	{ return m_bActive; }
	const ImVec2	GetSize()	{ return m_v2Size; }

	// Setter
	void SetName(const string& _name)			{ m_strName = _name; }
	void Activate()								{ m_bActive = true; }
	void Deactivate()							{ m_bActive = false; }
	void SetSize(ImVec2 _size)					{ m_v2Size = _size; }
	void SetWindowFlag(ImGuiWindowFlags _flag)	{ m_eWindowFlags = _flag; }
	void SetParentUI(CUI* _parent)				{ m_pParent = _parent; }

public:
	void AddChildUI(CUI* _child) { m_vecChildren.push_back(_child); _child->SetParentUI(this); }

public:
	virtual void Tick() {}
	virtual void SetWindowOption() {}	// UIâ �ɼ� ����
	virtual void Render() final;
	virtual void Render_Update() = 0;	// UIâ ���� ����
};

