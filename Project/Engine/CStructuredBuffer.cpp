#include "pch.h"
#include "CStructuredBuffer.h"

CStructuredBuffer::CStructuredBuffer()
	: m_iElementSize(0)
	, m_iElementCnt(0)
	, m_eType(SB_TYPE::READ_ONLY)
{
	SetName(L"StructuredBuffer");
}

CStructuredBuffer::~CStructuredBuffer()
{
}

int32 CStructuredBuffer::Create(UINT _elementSize, UINT _elementCnt, SB_TYPE _type, void* _sysMem)
{
	HRESULT hr = S_OK;

	// ����ȭ���� ����
	{
		// ����ȭ ������ ũ�Ⱑ 16�������� Ȯ��
		if (_elementSize % 16)
		{
			MessageBoxA(nullptr, "Structured Buffer Size Incorrect", "CStructuredBuffer Error", MB_OK);
			_exit(EXIT_FAILURE);
		}

		m_iElementSize = _elementSize;
		m_iElementCnt = _elementCnt;

		D3D11_BUFFER_DESC tDesc = {};
		{
			tDesc.ByteWidth = m_iElementSize * m_iElementCnt;
			tDesc.Usage = D3D11_USAGE_DEFAULT;
			tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			tDesc.CPUAccessFlags = 0;
			tDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			tDesc.StructureByteStride = m_iElementSize;
		}

		// �Ѱ��� �����Ͱ� ���� ���
		if (nullptr == _sysMem)
		{
			hr = DEVICE->CreateBuffer(&tDesc, nullptr, m_SB.GetAddressOf());
		}
		// �Ѱ��� �����Ͱ� �ִ� ���
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

	// Shader Resource View ����
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


