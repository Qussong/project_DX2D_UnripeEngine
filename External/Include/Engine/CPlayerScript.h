#pragma once
#include "CScript.h"

class CPlayerScript :
    public CScript
{
    using Super = CScript;

public:
    CPlayerScript();
    virtual ~CPlayerScript();

private:
    float   m_fSpeed;

private:
    virtual void Texture() override;  
    virtual void Animation() override;

public:
    virtual void Begin() override;
    virtual void Tick() override;

public:
    virtual void BeginOverlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider) override;
    virtual void Overlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider) override;
    virtual void EndOverlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider) override;
};