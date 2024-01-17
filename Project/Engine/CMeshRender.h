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
    // Owner(GameObject) ∞° µπ∑¡¡‹
    virtual void Begin();
    virtual void Tick();
    virtual void FinalTick();
    virtual void UpdateData();
    virtual void Render();
};

