#pragma once

class CUI
{
public:
	CUI(const string& _strName, const string& _strID);
	virtual ~CUI();

private:
	string		m_strName;
	string		m_strID;
	bool		m_bActive;

public:
	// Getter
	const string&	GetName() { return m_strName; }
	const string&	GetID() { return m_strID; }
	bool			IsActive() { return m_bActive; }

	// Setter
	void SetName(const string& _name) { m_strName = _name; }
	void Activate() { m_bActive = true; }
	void Deactivate() { m_bActive = false; }

public:
	virtual void Tick() {}
	virtual void Render() final;
	virtual void Render_Update() = 0;
};

