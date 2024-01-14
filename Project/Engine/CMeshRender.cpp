#include "pch.h"
#include "CMeshRender.h"

CMeshRender::CMeshRender()
	: Super(COMPONENT_TYPE::MESHRENDER)
{
	SetName(L"MeshRender");
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::Begin()
{
}

void CMeshRender::Tick()
{
}

void CMeshRender::FinalTick()
{
}

void CMeshRender::UpdateData()
{
	if (nullptr != GetGraphicShader())
		GetGraphicShader()->UpdateData();

	GetMesh()->UpdateData();
	GetOwner()->Transform()->UpdateData();
}

void CMeshRender::Render()
{
	if (nullptr == GetMesh() || nullptr == GetGraphicShader())
		return;

	UpdateData();
	GetMesh()->Render();
}

