#include "pch.h"
#include "CConstantBuffer.h"

CConstantBuffer::CConstantBuffer(CB_TYPE _type)
	: m_elementSize(0)
	, m_elementCnt(0)
	, m_eType(_type)
{
	SetName(L"ConstantBuffer");
}

CConstantBuffer::~CConstantBuffer()
{
}

void CConstantBuffer::Create(UINT _size, UINT _cnt)
{
	m_elementSize = _size;
	m_elementCnt = _cnt;

	D3D11_BUFFER_DESC desc = {};
	{
		desc.ByteWidth = m_elementSize * m_elementCnt;	// 상수버퍼 총 크기
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = m_elementSize;		// 상수버퍼 요소 하나 크기
	}

	HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, m_CB.GetAddressOf());
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "Constant Buffer Create Failed", "Constant Buffer Error", MB_OK);
		_exit(EXIT_FAILURE);
	}
}

void CConstantBuffer::SetData(void* _src, UINT _cnt)
{
	if (0 == _cnt)
		_cnt = m_elementCnt;

	// CPU -> GPU (Binding)
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(m_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, _src, m_elementSize * _cnt);
	CONTEXT->Unmap(m_CB.Get(), 0);
}

void CConstantBuffer::UpdateData()
{
	CONTEXT->VSSetConstantBuffers((UINT)m_eType, 1, m_CB.GetAddressOf());
	//CONTEXT->HSSetConstantBuffers((UINT)m_eType, 1, m_CB.GetAddressOf());
	//CONTEXT->DSSetConstantBuffers((UINT)m_eType, 1, m_CB.GetAddressOf());
	//CONTEXT->GSSetConstantBuffers((UINT)m_eType, 1, m_CB.GetAddressOf());
	CONTEXT->PSSetConstantBuffers((UINT)m_eType, 1, m_CB.GetAddressOf());
}
