#pragma once

class CTestMonsterScript
	: public CMonsterScript
{
public:
	CTestMonsterScript();
	virtual ~CTestMonsterScript();

private:
	virtual void Texture() override;	// Texture 로드
	virtual void Animation() override;	// Animation 생성

public:
	virtual void Tick() override;

public:
	virtual void BeginOverlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider);
	virtual void Overlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider);
	virtual void EndOverlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider);
};

