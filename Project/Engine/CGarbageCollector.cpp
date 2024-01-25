#include "pch.h"
#include "CGarbageCollector.h"

CGarbageCollector::CGarbageCollector()
{
}

CGarbageCollector::~CGarbageCollector()
{
}

void CGarbageCollector::Tick()
{
	int32 size = m_vecEntity.size();
	if (100 < size)
	{

	}
}

void CGarbageCollector::Add(CEntity* _entity)
{
	m_vecEntity.push_back(_entity);
}
