#pragma once

class CGarbageCollector
	: CSingleton<CGarbageCollector>
{
	SINGLETON(CGarbageCollector);

private:
	vector<CEntity*>	m_vecEntity;
	uint32				m_iMaxCapacity;

public:
	void Tick();
	void Add(CEntity* _entity);
};

