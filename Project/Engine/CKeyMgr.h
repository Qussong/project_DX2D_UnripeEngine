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
	short			m_sMouseWheel;

public:
	KEY_STATE	GetKeyState(KEY _key) { return m_vecKeyData[(int)_key].eState; }
	Vec2		GetMouseCurPos() { return m_v2CurMousePos; }
	Vec2		GetMouseDragDir() { return m_v2MouseDragDir; }
	short		GetMouseWheel() { return m_sMouseWheel; }

	void		SetMouseWheel(short _wheel) { m_sMouseWheel = _wheel; }

public:
	void Init();
	void Tick();
};