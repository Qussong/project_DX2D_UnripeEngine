#pragma once

class CLevel;

class CLevelMgr
	: public CSingleton<CLevelMgr>
{
	SINGLETON(CLevelMgr);

private:
	vector<CLevel*> m_vecLevel;
	CLevel*			m_pCurLevel;

public:
	CLevel* GetCurrentLevel() { return m_pCurLevel; }
	
public:
	void Init();
	void Tick();
};