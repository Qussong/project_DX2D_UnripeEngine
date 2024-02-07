#include "pch.h"
#include "CTestMonsterScript.h"

CTestMonsterScript::CTestMonsterScript()
{
	SetName(L"TestMonsterScript");
}

CTestMonsterScript::~CTestMonsterScript()
{
}

void CTestMonsterScript::Texture()
{
	Ptr<CTexture> pTex = nullptr;
	pTex = M_ASSET->LoadTexture(L"penguin_hit", L"Test\\penguin_hit.png");
	pTex = M_ASSET->LoadTexture(L"penguin_jump_atlas", L"Test\\penguin_jump.png");

	// Set
	pTex = M_ASSET->FindAsset<CTexture>(L"penguin_hit");
	GetOwner()->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);
}

void CTestMonsterScript::Animation()
{
	Ptr<CTexture> pAtlasTex = M_ASSET->FindAsset<CTexture>(L"penguin_jump_atlas");
	GetOwner()->Animator2D()->Create(L"penguin_jump_ani", pAtlasTex, 4, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), Vec2(50.f, 50.f), 10);

	// Set
	GetOwner()->Animator2D()->Play(L"penguin_jump_ani", true);
}

void CTestMonsterScript::Tick()
{
}

void CTestMonsterScript::BeginOverlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider)
{
}

void CTestMonsterScript::Overlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider)
{
}

void CTestMonsterScript::EndOverlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider)
{
}
