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
	if (GetOwner()->IsBelongLevel()
		&& !GetOwner()->IsLoadAsset())
	{
		Texture();
		Animation();

		GetOwner()->SetLoadAsset(true);
	}
}