#pragma once

class CTaskMgr
	: public CSingleton<CTaskMgr>
{
	SINGLETON(CTaskMgr);

private:
	vector<tTask> m_vecTask;

public:
	void AddTask(const tTask& _task) { m_vecTask.push_back(_task); }

public:
	void Tick();
};