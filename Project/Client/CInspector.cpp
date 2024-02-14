#include "pch_client.h"
#include "CInspector.h"

CInspector::CInspector()
	: Super("Inspector", "##Inspector")
	, m_pTargetObj(nullptr)
	, m_arrCompUI{}
{
	// 자식 UI 생성
	m_arrCompUI[(UINT)COMPONENT_TYPE::TRANSFORM] = new CTransformUI;
	AddChildUI(m_arrCompUI[(UINT)COMPONENT_TYPE::TRANSFORM]);

	m_arrCompUI[(UINT)COMPONENT_TYPE::MESHRENDER] = new CMeshRenderUI;
	AddChildUI(m_arrCompUI[(UINT)COMPONENT_TYPE::MESHRENDER]);
}

CInspector::~CInspector()
{
}

void CInspector::SetTargetObject(CGameObject* _obj)
{
	m_pTargetObj = _obj;

	for (size_t i = 0; i < (UINT)COMPONENT_TYPE::RENDER_END; ++i)
	{
		if (nullptr != m_arrCompUI[i])
			m_arrCompUI[i]->SetTargetObj(_obj);
	}
}

void CInspector::SetTargetAsset(Ptr<CAsset> _asset)
{
	m_pTargetAsset = _asset;
}

void CInspector::Render_Update()
{
	if (nullptr == m_pTargetObj)
		return;

	string strName = string(m_pTargetObj->GetName().begin(), m_pTargetObj->GetName().end());
	ImGui::Text(strName.c_str());
}  