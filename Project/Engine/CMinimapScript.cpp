#include "pch.h"
#include "CMinimapScript.h"

CMinimapScript::CMinimapScript()
{
}

CMinimapScript::~CMinimapScript()
{
}

void CMinimapScript::Tick()
{
	if (nullptr != GetOwner())
	{
		//Ptr<CTexture> pTex = M_ASSET->FindAsset<CTexture>(L"PostProcessTex");
		Ptr<CTexture> pTex = M_RENDER->GetPostProcessTex();
		GetOwner()->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);
	}
}

