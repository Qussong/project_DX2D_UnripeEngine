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

void CMeshRender::UpdateData()
{
	GetMesh()->UpdateData();
	GetMaterial()->UpdateData();

	GetOwner()->Transform()->UpdateData();
}

void CMeshRender::Render()
{
	// 화면상에 출력되기 위해선 Mesh,Shader가 둘다 있어야한다.
	if (nullptr == GetMesh() || nullptr == GetMaterial())
		return;

	UpdateData();
	GetMesh()->Render();
}

