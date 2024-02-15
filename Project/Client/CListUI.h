#pragma once

class CListUI
	: public CUI
{
	using Super = CUI;

public:
	CListUI();
	virtual ~CListUI();

private:
	vector<string>	m_vecStr;
	string			m_strDoubleClicked;
	CALL_BACK_1		m_pCallBackFunc;

public:
	void AddString(const string& _str) { m_vecStr.push_back(_str); }
	void AddString(const vector<string>& _vecStr) { m_vecStr.insert(m_vecStr.end(), _vecStr.begin(), _vecStr.end()); }
	void SetDBClickCallBack(CALL_BACK_1 _call) { m_pCallBackFunc = _call; }
	string GetDoubleClicked() { return m_strDoubleClicked; }

public:
	virtual void Deactivate() override;
	virtual void SetWindowOption() override {};
	virtual void Render_Update() override;
};

