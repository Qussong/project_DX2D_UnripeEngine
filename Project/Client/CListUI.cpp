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

            // ����Ʈ �� �ش� �׸��� Ŭ���Ǹ� ���̶���Ʈ �ɾ���
            if (is_selected)
                ImGui::SetItemDefaultFocus();

            // ����Ʈ �׸� �� ����Ŭ���� �߻��Ѵٸ�            
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
