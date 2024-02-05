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
	// Collider2D Comp 를 가지지 않은 객체의 중심도 표시하기위해 MeshRender의 FinalTick()에 구현
	// 이 외의 Collider 객체는 Collider2D의 FinalTick()에서 추가된다.
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
	// 화면상에 출력되기 위해선 Mesh,Shader가 둘다 있어야한다.
	if (nullptr == GetMesh() || nullptr == GetMaterial())
		return;

	UpdateData();
	GetMesh()->Render();
}

