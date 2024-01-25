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
	// ȭ��� ��µǱ� ���ؼ� Mesh,Shader�� �Ѵ� �־���Ѵ�.
	if (nullptr == GetMesh() || nullptr == GetMaterial())
		return;

	UpdateData();
	GetMesh()->Render();
}

