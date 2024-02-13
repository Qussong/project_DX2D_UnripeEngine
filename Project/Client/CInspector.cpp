#include "pch_client.h"
#include "CInspector.h"

CInspector::CInspector()
	: Super("Inspector", "##Inspector")
	, m_pTargetObj(nullptr)
{
}

CInspector::~CInspector()
{
}

void CInspector::SetTargetObject(CGameObject* _obj)
{
	m_pTargetObj = _obj;
}

void CInspector::SetTargetAsset(Ptr<CAsset> _asset)
{
	m_pTargetAsset = _asset;
}

void CInspector::Tick()
{
}

void CInspector::Render_Update()
{
	if (nullptr == m_pTargetObj)
		return;

	const wstring& wstrName = m_pTargetObj->GetName();
	string strName = string(strName.begin(), strName.end());
	ImGui::Text(strName.c_str());
}  