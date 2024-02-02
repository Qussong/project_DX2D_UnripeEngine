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
	CAnimator2D* pAni2D = GetOwner()->Animator2D();
	if (nullptr != pAni2D)
		pAni2D->UpdateData();
	else
		pAni2D->Clear();

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

