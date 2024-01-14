#include "pch.h"
#include "CComponent.h"

CComponent::CComponent(COMPONENT_TYPE _type)
	: m_eType(_type)
	, m_pOwner(nullptr)
{
}

CComponent::~CComponent()
{
}
