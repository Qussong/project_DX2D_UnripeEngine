#include "pch.h"
#include "CGarbageCollector.h"

CGarbageCollector::CGarbageCollector()
	: m_iMaxCapacity(100)
{
}

CGarbageCollector::~CGarbageCollector()
{
	Lazy::DelVector(m_vecEntity);
}

void CGarbageCollector::Tick()
{
	size_t size = m_vecEntity.size();
	if (m_iMaxCapacity < size)
	{
		Lazy::DelVector(m_vecEntity);
	}
}

void CGarbageCollector::Add(CEntity* _entity)
{
	m_vecEntity.push_back(_entity);
}
