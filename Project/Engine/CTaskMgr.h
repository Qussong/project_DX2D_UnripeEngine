#pragma once

class CTaskMgr
	: public CSingleton<CTaskMgr>
{
	SINGLETON(CTaskMgr);

private:
	vector<tTask> m_vecTask;

private:
	void AddObject(size_t _idx);
	void SubObject(size_t _idx);

public:
	void AddTask(const tTask& _task) { m_vecTask.push_back(_task); }

public:
	void Tick();
};