#include "pch_client.h"
#include "CUI.h"

CUI::CUI(const string& _strName, const string& _strID)
	: m_strName(_strName)
	, m_strID(_strID)
	, m_bActive(true)
	, m_eWindowFlags(0)
{
}

CUI::~CUI()
{
}

void CUI::Render()
{
	if (m_bActive)
	{
		// set window option
		SetWindowOption();

		// start
		ImGui::Begin(string(m_strName + m_strID).c_str(), &m_bActive, m_eWindowFlags);

		// window update
		Render_Update();

		// end
		ImGui::End();
	}
}
