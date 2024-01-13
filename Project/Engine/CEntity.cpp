#include "pch.h"
#include "CEntity.h"

UINT CEntity::g_iNextID = 0;

CEntity::CEntity()
	: m_iID(g_iNextID++)
	, m_strName(L"")
{
}

CEntity::~CEntity()
{
}
