#include "pch_client.h"
#include "CListUI.h"

CListUI::CListUI()
	: Super("ListUI", "##ListUI")
	, m_pCallBackFunc(nullptr)
{
}

CListUI::~CListUI()
{
}

void CListUI::Deactivate()
{
	CUI::Deactivate();

	m_vecStr.clear();
	ImGui::SetWindowFocus(nullptr);
}

void CListUI::Render_Update()
{
    ImVec2 vWinSize = ImGui::GetWindowContentRegionMax();
    vWinSize.y -= 27;

    static int item_current_idx = 0; // Here we store our selection data as an index.
    if (ImGui::BeginListBox("##ListBox", vWinSize))
    {
        for (int i = 0; i < m_vecStr.size(); i++)
        {
            const bool is_selected = (item_current_idx == i);

            if (ImGui::Selectable(m_vecStr[i].c_str(), is_selected))
                item_current_idx = i;

            // 리스트 중 해당 항목이 클릭되면 하이라이트 걸어줌
            if (is_selected)
                ImGui::SetItemDefaultFocus();

            // 리스트 항목 중 더블클릭이 발생한다면            
            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                m_strDoubleClicked = m_vecStr[i];

                if (nullptr != m_pCallBackFunc)
                    m_pCallBackFunc((DWORD_PTR)m_strDoubleClicked.c_str());

                Deactivate();
            }
        }
        ImGui::EndListBox();
    }
}
