#pragma once

class CLevel;

class CLevelMgr
	: public CSingleton<CLevelMgr>
{
	SINGLETON(CLevelMgr);

private:
	CLevel*		m_pCurLevel;

public:
	CLevel* GetCurrentLevel() { return m_pCurLevel; }
	
	// test
	CGameObject* m_pTestObjet = nullptr;
	void Test();

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();
};