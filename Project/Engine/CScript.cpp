#include "pch.h"
#include "CScript.h"

CScript::CScript()
	: Super(COMPONENT_TYPE::SCRIPT)
{
	SetName(L"Script");
}

CScript::~CScript()
{
}

void CScript::Begin()
{
	if (GetOwner()->IsBelongLevel())
	{
		// Asset Load (한번만 진행)
		if (!GetOwner()->IsLoadAsset())
		{
			Texture();
			Animation();
			GetOwner()->SetLoadAsset(true);
		}

		// 매 틱마다 Begin에서 갱신되야 하는 작업이 있다면 추가

	}
}