#pragma once

class CKeyMgr
	: public CSingleton<CKeyMgr>
{
	SINGLETON(CKeyMgr);

private:
	vector<KeyData>	m_vecKeyData;
	Vec2			m_v2CurMousePos;
	Vec2			m_v2PrevMousePos;
	Vec2			m_v2MouseDragDir;

public:
	KEY_STATE	GetKeyState(KEY _key) { return m_vecKeyData[(int)_key].eState; }
	Vec2		GetMouseCurPos() { return m_v2CurMousePos; }
	Vec2		GetMouseDragDir() { return m_v2MouseDragDir; }

public:
	void Init();
	void Tick();
};