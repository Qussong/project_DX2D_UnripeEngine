#pragma once

class CGarbageCollector
	: CSingleton<CGarbageCollector>
{
	SINGLETON(CGarbageCollector);

private:
	vector<CEntity*>	m_vecEntity;

public:
	void Tick();
	void Add(CEntity* _entity);
};

