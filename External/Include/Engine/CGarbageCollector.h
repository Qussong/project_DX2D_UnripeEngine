#pragma once

class CGarbageCollector
	: public CSingleton<CGarbageCollector>
{
	SINGLETON(CGarbageCollector);

private:
	vector<CEntity*>	m_vecEntity;
	uint32				m_iMaxCapacity;

public:
	void Add(CEntity* _entity);

public:
	void Tick();
};

