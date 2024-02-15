#include "pch_client.h"
#include "CComponentUI.h"

CComponentUI::CComponentUI(const string& _name, const string& _id, COMPONENT_TYPE _type)
	: Super(_name, _id)
	, m_pTargetObj(nullptr)
	, m_eType(_type)
	, m_strCompTitle(_name)
{
	SetCompTitle(_name);
}

CComponentUI::~CComponentUI()
{
}

void CComponentUI::SetTargetObj(CGameObject* _obj)
{
	m_pTargetObj = _obj;

	if (nullptr == m_pTargetObj)
	{
		 Deactivate();
	}
	else
	{
		if (nullptr == m_pTargetObj->GetComponent(m_eType))
			Deactivate();
		else
			Activate();
	}	

}

void CComponentUI::Render_Update()
{
	ImGui::Separator();

	ImGui::PushID(0);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::ImColor(1.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, .6f, .6f));	// 색상, 채도, 명도
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 1.f, .6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));

	ImGui::Button(m_strCompTitle.c_str());

	ImGui::PopStyleColor(4);
	ImGui::PopID();
}