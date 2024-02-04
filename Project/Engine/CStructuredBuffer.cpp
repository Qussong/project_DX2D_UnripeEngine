#include "pch.h"
#include "CStructuredBuffer.h"

CStructuredBuffer::CStructuredBuffer()
	: m_iElementSize(0)
	, m_iElementCnt(0)
	, m_eType(SB_TYPE::READ_ONLY)
	, m_bSysMemMove(false)
{
	SetName(L"StructuredBuffer");
}

CStructuredBuffer::~CStructuredBuffer()
{
}

void CStructuredBuffer::SetData(void* _src, UINT _elementCnt)
{
	if (false == m_bSysMemMove)
	{
		MessageBoxA(nullptr, "System Memory Not Move", "CStructuredBuffer Error", MB_OK);
		_exit(EXIT_FAILURE);
	}

	if (nullptr == _src)
		return;

	// 인자로 들어온 elementCnt가 0이면 구조화버퍼에 넣어줄 수 있는 최대 크기로 설정해준다.
	UINT iDataSize = m_iElementSize * _elementCnt;
	if (0 == iDataSize)
	{
		iDataSize = GetBufferSize();
	}

	// 인자로 들어온 elementCnt가 구조화버퍼에 넣을 수 있는 최대 크기를 넘어서는 경우
	if (m_iElementCnt < _elementCnt)
	{
		m_SB = nullptr;
		Create(m_iElementSize, _elementCnt, m_eType, m_bSysMemMove, nullptr);
	}

	// CPU -> CPU WriteBuffer
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(m_SB_Write.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, _src, iDataSize);
	CONTEXT->Unmap(m_SB_Write.Get(), 0);

	// Write SB Buffer -> Main SB Buffer
	CONTEXT->CopyResource(m_SB.Get(), m_SB_Write.Get());
}

void CStructuredBuffer::GetData(void* _dest, UINT _elementCnt)
{
	if (false == m_bSysMemMove)
	{
		MessageBoxA(nullptr, "System Memory Not Move", "CStructuredBuffer Error", MB_OK);
		_exit(EXIT_FAILURE);
	}

	// 구조화 버퍼에서 가져올 데이터의 사이즈
	UINT iDestSize = m_iElementSize * _elementCnt;

	// Main SB Buffer -> Read SB Buffer
	CONTEXT->CopyResource(m_SB_Read.Get(), m_SB.Get());

	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(m_SB_Read.Get(), 0, D3D11_MAP::D3D11_MAP_READ, 0, &tSub);
	memcpy(_dest, tSub.pData, iDestSize);
	CONTEXT->Unmap(m_SB_Read.Get(), 0);
}

int32 CStructuredBuffer::Create(UINT _elementSize, UINT _elementCnt, SB_TYPE _type, bool _sysMemMove, void* _sysMem)
{
	HRESULT hr = S_OK;

	// 구조화버퍼 생성
	{
		// 구조화 버퍼의 크기가 16단위인지 확인
		if (_elementSize % 16)
		{
			MessageBoxA(nullptr, "Structured Buffer Size Incorrect", "CStructuredBuffer Error", MB_OK);
			_exit(EXIT_FAILURE);
		}

		m_iElementSize = _elementSize;
		m_iElementCnt = _elementCnt;
		m_eType = _type;
		m_bSysMemMove = _sysMemMove;

		D3D11_BUFFER_DESC tDesc = {};
		{
			tDesc.ByteWidth = m_iElementSize * m_iElementCnt;
			tDesc.Usage = D3D11_USAGE_DEFAULT;
			tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			tDesc.CPUAccessFlags = 0;
			tDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			tDesc.StructureByteStride = m_iElementSize;
		}

		// 넘겨줄 데이터가 없는 경우
		if (nullptr == _sysMem)
		{
			hr = DEVICE->CreateBuffer(&tDesc, nullptr, m_SB.GetAddressOf());
		}
		// 넘겨줄 데이터가 있는 경우
		else
		{
			D3D11_SUBRESOURCE_DATA tSub = {};
			tSub.pSysMem = _sysMem;
			hr = DEVICE->CreateBuffer(&tDesc, &tSub, m_SB.GetAddressOf());
		}
	}

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "Create StructuredBuffer Failed", "CStructuredBuffer Error", MB_OK);
		return E_FAIL;
	}

	// Shader Resource View 생성
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC tDesc = {};
		{
			tDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			tDesc.Buffer.NumElements = _elementCnt;
		}
		hr = DEVICE->CreateShaderResourceView(m_SB.Get(), &tDesc, m_SRV.GetAddressOf());
	}

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "Create ShaderResourceView Failed", "CStructuredBuffer Error", MB_OK);
		return E_FAIL;
	}

	if (m_bSysMemMove)
	{
		D3D11_BUFFER_DESC tDesc = {};
		tDesc.ByteWidth = m_iElementSize * m_iElementCnt;
		tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		tDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		tDesc.StructureByteStride = m_iElementSize;

		// Read
		tDesc.Usage = D3D11_USAGE_DEFAULT;
		tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		hr = DEVICE->CreateBuffer(&tDesc, nullptr, m_SB_Read.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "Create StructuredBuffer Read Buffer Failed", "CStructuredBuffer Error", MB_OK);
			return E_FAIL;
		}

		// Write
		tDesc.Usage = D3D11_USAGE_DYNAMIC;
		tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		hr = DEVICE->CreateBuffer(&tDesc, nullptr, m_SB_Write.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "Create StructuredBuffer Write Buffer Failed", "CStructuredBuffer Error", MB_OK);
			return E_FAIL;
		}
	}

	return hr;
}

void CStructuredBuffer::UpdateData(UINT _registerNum)
{
	CONTEXT->VSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
	//CONTEXT->HSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
	//CONTEXT->DSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
	//CONTEXT->GSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->PSSetShaderResources(_registerNum, 1, m_SRV.GetAddressOf());
}


