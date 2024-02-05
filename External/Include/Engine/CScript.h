#pragma once
#include "CComponent.h"

class CScript :
    public CComponent
{
    using Super = CComponent;

public:
    CScript();
    virtual ~CScript();

private:
    uint32 m_iScriptType;

private:
    virtual void Texture() {}   // Texture 로드
    virtual void Animation() {} // Animation 생성

public:
    virtual void Begin() override {};
    virtual void Tick() override {};
    virtual void FinalTick() final {}
    virtual void UpdateData() final {}

public:
    virtual void BeginOverlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider) {};
    virtual void Overlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider) {};
    virtual void EndOverlap(CCollider2D* _collider, CGameObject* _otherObj, CCollider2D* _otherCollider) {};
};