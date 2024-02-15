#include "pch_client.h"
#include "CTransformUI.h"

CTransformUI::CTransformUI()
	: Super("TransformUI", "##TransformUI", COMPONENT_TYPE::TRANSFORM)
{
	SetSize(ImVec2(0.f, 120.f));
}

CTransformUI::~CTransformUI()
{
}

void CTransformUI::Render_Update()
{
	CGameObject* pTarget = GetTargetObj();
	if (nullptr == pTarget)
		return;

	CTransform* pTransform = pTarget->Transform();

	// 부모 Render_Update() 갱신
	CComponentUI::Render_Update();

	Vec3 v3Pos	 = pTransform->GetLocalPos();
	Vec3 v3Scale = pTransform->GetLocalScale();
	Vec3 v3Rot	 = pTransform->GetLocalRotation();
	v3Rot = (v3Rot / XM_PI) * 180.f;	// To Degree

	ImGui::Text("Local Pos   : "); ImGui::SameLine(); ImGui::DragFloat3("##LocalPos", v3Pos);
	ImGui::Text("Local Scale : "); ImGui::SameLine(); ImGui::DragFloat3("##LocalScale", v3Scale);
	ImGui::Text("Local Rot   : "); ImGui::SameLine(); ImGui::DragFloat3("##LocalRot", v3Rot);

	v3Rot = (v3Rot / 180.f) * XM_PI;	// To Radian
	pTransform->SetLocalPos(v3Pos);
	pTransform->SetLocalScale(v3Scale);
	pTransform->SetLocalRotation(v3Rot);

	// Absolute
	bool bAbsolute = GetTargetObj()->Transform()->IsAffectScale();
	ImGui::Text("Scale Absolute "); ImGui::SameLine(); ImGui::Checkbox("##ScaleAbsolute", &bAbsolute);
	GetTargetObj()->Transform()->SetAffectScale(bAbsolute);
}