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

public:
    //virtual void Begin() = 0;
    //virtual void Tick() = 0;
    //virtual void FinalTick() = 0;
    //virtual void UpdateData() = 0;
};

