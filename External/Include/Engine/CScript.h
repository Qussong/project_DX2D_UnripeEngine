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
};

