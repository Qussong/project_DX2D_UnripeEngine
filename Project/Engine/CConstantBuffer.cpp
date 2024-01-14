#include "pch.h"
#include "CConstantBuffer.h"

CConstantBuffer::CConstantBuffer()
{
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
		desc.ByteWidth = m_elementSize * m_elementCnt;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = m_elementSize;
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
	{
		_cnt = m_elementCnt;
	}

	// Binding , CPU -> GPU 
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(m_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, _src, m_elementSize * _cnt);
	CONTEXT->Unmap(m_CB.Get(), 0);
}

void CConstantBuffer::UpdateData(UINT _registerNum)
{
	CONTEXT->VSSetConstantBuffers(_registerNum, 1, m_CB.GetAddressOf());
	CONTEXT->PSSetConstantBuffers(_registerNum, 1, m_CB.GetAddressOf());
}
