#pragma once

class CLevel;

class CLevelMgr
	: public CSingleton<CLevelMgr>
{
	SINGLETON(CLevelMgr);

private:
	CLevel*		m_pCurLevel;

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();
};

