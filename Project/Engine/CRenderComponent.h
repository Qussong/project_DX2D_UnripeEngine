#pragma once
#include "CComponent.h"

class CMesh;
class CGraphicShader;

class CRenderComponent :
    public CComponent
{
    using Super = CComponent;

public:
    CRenderComponent(COMPONENT_TYPE _type);
    virtual ~CRenderComponent();

private:
    CMesh*              m_Mesh;
    CGraphicShader*     m_Shader;

public:
    void SetMesh(CMesh* _mesh) { m_Mesh = _mesh; }
    void SetGraphicShader(CGraphicShader* _shader) { m_Shader = _shader; }

    CMesh* GetMesh() { return m_Mesh; }
    CGraphicShader* GetGraphicShader() { return m_Shader; }

public:
    virtual void Render() = 0;
};

