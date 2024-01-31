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
	
	CGameObject* m_pTestObj = nullptr;

public:
	void Init();
	void Tick();
	void FinalTick();
};