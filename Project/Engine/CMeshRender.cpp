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
	GetOwner()->Transform()->UpdateData();
	GetGraphicShader()->UpdateData();
}

void CMeshRender::Render()
{
	// ȭ��� ��µǱ� ���ؼ� Mesh,Shader�� �Ѵ� �־���Ѵ�.
	if (nullptr == GetMesh() || nullptr == GetGraphicShader())
		return;

	UpdateData();
	GetMesh()->Render();
}

