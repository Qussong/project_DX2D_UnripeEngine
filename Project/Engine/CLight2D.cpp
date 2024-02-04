#include "pch.h"
#include "CLight2D.h"

CLight2D::CLight2D()
	: Super(COMPONENT_TYPE::LIGHT2D)
{
	SetName(L"Light2D");
}

CLight2D::~CLight2D()
{
}

void CLight2D::FinalTick()
{
	// ±¤¿ø µî·Ï
	M_RENDER->RegisterLight2D(this);
}