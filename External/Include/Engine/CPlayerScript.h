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

public:
    virtual void Begin() override {};
    virtual void Tick() override;
    virtual void FinalTick() override {};
    virtual void UpdateData() override {};
};

