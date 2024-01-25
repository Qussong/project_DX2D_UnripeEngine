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
    CMesh*              m_pMesh;
    CMaterial*          m_pMaterial;

public:
    void SetMesh(CMesh* _mesh) { m_pMesh = _mesh; }
    void SetMaterial(CMaterial* _material) { m_pMaterial = _material; }

    CMesh* GetMesh() { return m_pMesh; }
    CMaterial* GetMaterial() { return m_pMaterial; }

public:
    virtual void Begin() override {};
    virtual void Tick() override {};
    virtual void FinalTick() override {};
    virtual void UpdateData() override {};
    virtual void Render() = 0;
};

