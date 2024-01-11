#pragma once

class CKeyMgr
	: public CSingleton<CKeyMgr>
{
	SINGLETON(CKeyMgr);

private:
	vector<KeyData>	m_vecKeyData;
	Vec2			m_vMousePos;

public:
	KEY_STATE GetKeyState(KEY _key) { return m_vecKeyData[(int)_key].eState; }
	Vec2 GetMousePos() { return m_vMousePos; }

public:
	void Init();
	void Tick();
};

