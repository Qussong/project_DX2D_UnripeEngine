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

	// PostProcess
	Vec2 v2Resolution = GRAPHICS->GetResolution();
	UINT iWidth = v2Resolution.x;
	UINT iHeight = v2Resolution.y;
	DXGI_FORMAT eFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	UINT iBindFlag = D3D11_BIND_SHADER_RESOURCE;
	m_PostProcessTex = M_ASSET->CreateTexture(L"PostProcessTex", iWidth, iHeight, eFormat, iBindFlag);
}