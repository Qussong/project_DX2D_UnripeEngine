#pragma once

class CTimeMgr
	: public CSingleton<CTimeMgr>
{
	SINGLETON(CTimeMgr);

private:
	LARGE_INTEGER	m_frequency;
	LARGE_INTEGER	m_prevCnt;
	LARGE_INTEGER	m_curCnt;
	float			m_deltaTime;

	float			m_fAccTime;	// Accumulated : 누적된, 쌓인
	int32			m_FPS;

public:
	float DeltaTime() { return m_deltaTime; }

public:
	void Init();
	void Tick();
};

