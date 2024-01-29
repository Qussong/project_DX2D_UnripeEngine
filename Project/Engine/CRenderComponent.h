#pragma once
#include "CComponent.h"

class CMesh;
class CMaterial;

class CRenderComponent :
    public CComponent
{
    using Super = CComponent;

public:
    CRenderComponent(COMPONENT_TYPE _type);
    virtual ~CRenderComponent();

private:
    Ptr<CMesh>              m_pMesh;
    Ptr<CMaterial>          m_pMaterial;

public:
    void SetMesh(Ptr<CMesh> _mesh)              { m_pMesh = _mesh; }
    void SetMaterial(Ptr<CMaterial> _material)  { m_pMaterial = _material; }

    Ptr<CMesh>      GetMesh()       { return m_pMesh; }
    Ptr<CMaterial>  GetMaterial()   { return m_pMaterial; }

public:
    virtual void Begin() override {};
    virtual void Tick() override {};
    virtual void FinalTick() override {};
    virtual void UpdateData() override {};
    virtual void Render() = 0;
};

