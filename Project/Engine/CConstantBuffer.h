#pragma once
#include "CEntity.h"

class CConstantBuffer :
    public CEntity
{
    using Super = CEntity;

public:
    CConstantBuffer();
    virtual ~CConstantBuffer();

private:
    ComPtr<ID3D11Buffer>	m_CB;   // ConstantBuffer

    UINT	                m_elementSize;
    UINT	                m_elementCnt;

public:
    void Create(UINT _size, UINT _cnt);
    void SetData(void* _src, UINT _cnt = 0);    // Binding
    void UpdateData(UINT _registerNum);
};

// ������� ���� ����ü ����
extern tTransform g_tTransform;