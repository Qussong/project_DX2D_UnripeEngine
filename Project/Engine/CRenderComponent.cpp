#include "pch.h"
#include "CRenderComponent.h"

CRenderComponent::CRenderComponent(COMPONENT_TYPE _type)
	: Super(_type)
{
	SetName(L"RenderComponent");
}

CRenderComponent::~CRenderComponent()
{
}