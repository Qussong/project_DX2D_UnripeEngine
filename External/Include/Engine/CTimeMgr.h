#pragma once

class CTimeMgr
	: public CSingleton<CTimeMgr>
{
	SINGLETON(CTimeMgr);

private:
	LARGE_INTEGER	m_lFrequency;
	LARGE_INTEGER	m_lPrevCnt;
	LARGE_INTEGER	m_lCurCnt;
	float			m_fDeltaTime;
	float			m_fAccTime;	// Accumulated : 누적된, 쌓인
	int32			m_iFPS;

public:
	float DeltaTime() { return m_fDeltaTime; }

public:
	void Init();
	void Tick();
};

