#include "pch.h"
#include "CRenderMgr.h"

void CRenderMgr::Init()
{
	Vec2 v2Resolution = GRAPHICS->GetResolution();

	// Debug
	m_pDebugObj = new CGameObject;
	m_pDebugObj->AddComponent(new CTransform);
	m_pDebugObj->AddComponent(new CMeshRender);

	// Light
	m_pLight2DBuffer = new CStructuredBuffer;
	m_pLight2DBuffer->Create(sizeof(tLight2D), LIGHT_MAX_CNT, SB_TYPE::READ_ONLY, true);

	// PostProcess
	m_PostProcessTex = M_ASSET->CreateTexture(L"PostProcessTex",
											(UINT)v2Resolution.x,
											(UINT)v2Resolution.y,
											DXGI_FORMAT_R8G8B8A8_UNORM,
											D3D11_BIND_SHADER_RESOURCE);

	// ViewUI
	m_ViewUITex = M_ASSET->CreateTexture(L"ViewUITex",
										(UINT)v2Resolution.x,
										(UINT)v2Resolution.y,
										DXGI_FORMAT_R8G8B8A8_UNORM,
										D3D11_BIND_SHADER_RESOURCE);
}