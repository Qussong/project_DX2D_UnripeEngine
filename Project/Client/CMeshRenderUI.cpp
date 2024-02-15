#include "pch_client.h"
#include "CMeshRenderUI.h"

CMeshRenderUI::CMeshRenderUI()
	: Super("MeshRenderUI", "##MeshRenderUI", COMPONENT_TYPE::MESHRENDER)
{
	SetSize(ImVec2(0.f, 100.f));
}

CMeshRenderUI::~CMeshRenderUI()
{
}

void CMeshRenderUI::Render_Update()
{
	CComponentUI::Render_Update();

	CGameObject* pTarget = GetTargetObj();
	CMeshRender* pMeshRender = pTarget->MeshRender();

	Ptr<CMesh> pMesh = pMeshRender->GetMesh();
	Ptr<CMaterial> pMtrl = pMeshRender->GetMaterial();

	string meshName = Lazy::ToString(pMesh->GetName().c_str());
	string mtrlName = Lazy::ToString(pMtrl->GetName().c_str());

	ImGui::Text("Mesh    ");
	ImGui::SameLine();
	ImGui::InputText("##MeshName", (char*)meshName.c_str(), meshName.length(), ImGuiInputTextFlags_ReadOnly);

	ImGui::Text("Material");
	ImGui::SameLine();
	ImGui::InputText("##Material", (char*)mtrlName.c_str(), mtrlName.length(), ImGuiInputTextFlags_ReadOnly);
}
