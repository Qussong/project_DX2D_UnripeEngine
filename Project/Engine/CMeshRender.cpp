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

void CMeshRender::FinalTick()
{
	// Collider2D Comp �� ������ ���� ��ü�� �߽ɵ� ǥ���ϱ����� MeshRender�� FinalTick()�� ����
	// �� ���� Collider ��ü�� Collider2D�� FinalTick()���� �߰��ȴ�.
	if (M_RENDER->IsDebugCheck())
	{
		Vec3 v3WorldPos = GetOwner()->Transform()->GetWorldPos();
		Vec3 v3Color = Vec3(1.f, 0.f, 1.f);
		GamePlayStatic::DrawDebugCross(v3WorldPos, 10.f, v3Color);
	}
}

void CMeshRender::UpdateData()
{
	CAnimator2D* pAnimator = GetOwner()->Animator2D();
	if (nullptr != pAnimator)
		pAnimator->UpdateData();
	else
		pAnimator->Clear();

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

