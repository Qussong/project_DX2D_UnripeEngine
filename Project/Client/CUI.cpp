#include "pch_client.h"
#include "CUI.h"

CUI::CUI(const string& _strName, const string& _strID)
	: m_strName(_strName)
	, m_strID(_strID)
	, m_bActive(true)
	, m_eWindowFlags(0)
	, m_pParent(nullptr)
{
}

CUI::~CUI()
{
	Lazy::DelVector(m_vecChildren);
}

void CUI::Render()
{
	// UI ��Ȱ��ȭ ������ ��� �Լ� ����
	if (false == m_bActive)
		return;

	// �θ� UI�� ���� ���
	if (nullptr == m_pParent)
	{
		// set window option
		SetWindowOption();

		// start
		ImGui::Begin(string(m_strName + m_strID).c_str(), &m_bActive, m_eWindowFlags);

		// window update
		Render_Update();

		// �ڽ� UI��ü Render
		for (CUI* ui : m_vecChildren)
			ui->Render();

		// end
		ImGui::End();
	}
	// �θ� UI�� �ִ� ���
	else
	{
		SetWindowOption();

		ImGui::BeginChild(string(m_strName + m_strID).c_str(), m_v2Size);

		Render_Update();

		for (CUI* ui : m_vecChildren)
			ui->Render();

		ImGui::EndChild();
	}
}
