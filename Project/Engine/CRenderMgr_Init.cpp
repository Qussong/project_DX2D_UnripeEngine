#include "pch.h"
#include "CRenderMgr.h"

void CRenderMgr::Init()
{
	// Debug
	m_pDebugObj = new CGameObject;
	m_pDebugObj->AddComponent(new CTransform);
	m_pDebugObj->AddComponent(new CMeshRender);

	// Light
	m_pLight2DBuffer = new CStructuredBuffer;
	m_pLight2DBuffer->Create(sizeof(tLight2D), LIGHT_MAX_CNT, SB_TYPE::READ_ONLY, true);
}