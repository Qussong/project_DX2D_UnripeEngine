#pragma once
#include "CRenderComponent.h"

class CMeshRender :
    public CRenderComponent
{
    using Super = CRenderComponent;

public:
    CMeshRender();
    virtual ~CMeshRender();

private:
    virtual void Begin() override {};
    virtual void Tick() override {};
    virtual void FinalTick() override;
    virtual void UpdateData() override;
    virtual void Render() override;
};

