#include "pch.h"
#include "CMesh.h"

CMesh::CMesh()
	: Super(ASSET_TYPE::MESH)
	, m_pVtxSysMem(nullptr)
	, m_iVtxCnt(0)
	, m_iIdxCnt(0)
	, m_pIdxSysMem(nullptr)
{
}

CMesh::~CMesh()
{
	if (nullptr != m_pVtxSysMem)
		delete m_pVtxSysMem;

	if (nullptr != m_pIdxSysMem)
		delete m_pIdxSysMem;
}

void CMesh::Create(void* _vtx, uint32 _vtxCnt, void* _idx, uint32 _idxCnt)
{
	// Vertex Buffer 생성
	{
		uint32 typeSize = sizeof(Vtx);
		m_iVtxCnt = _vtxCnt;

		D3D11_BUFFER_DESC desc = {};	// = ZeroMemory();
		{
			desc.ByteWidth = typeSize * m_iVtxCnt;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = typeSize;
		}

		D3D11_SUBRESOURCE_DATA tSubData = {};
		tSubData.pSysMem = _vtx;

		HRESULT hr = DEVICE->CreateBuffer(&desc, &tSubData, m_VB.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "Vertex Buffer Create Failed", "VertexBuffer Error", MB_OK);
			_exit(EXIT_FAILURE);
		}
	}

	// Index Buffer 생성
	{
		uint32 typeSize = sizeof(UINT);
		m_iIdxCnt = _idxCnt;

		D3D11_BUFFER_DESC desc = {};
		{
			desc.ByteWidth = typeSize * m_iIdxCnt;
			desc.Usage = D3D11_USAGE_DEFAULT;	// GPU 읽기, 쓰기
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = typeSize;
		}

		// 인덱스 버퍼에 들어갈 정점들의 초기 값 설정
		D3D11_SUBRESOURCE_DATA tSubData = {};
		tSubData.pSysMem = _idx;

		// Index Buffer
		HRESULT hr = DEVICE->CreateBuffer(&desc, &tSubData, m_IB.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "Index Buffer Create Failed", "Index Buffer Error", MB_OK);
			_exit(EXIT_FAILURE);
		}
	}

	// 정점, 인덱스에 대한 정보를 저장시켜두고 관리
	{
		m_pVtxSysMem = new Vtx[m_iVtxCnt];
		m_pIdxSysMem = new UINT[m_iIdxCnt];
		memcpy(m_pVtxSysMem, _vtx, sizeof(Vtx) * m_iVtxCnt);
		memcpy(m_pIdxSysMem, _idx, sizeof(UINT) * m_iIdxCnt);
	}
}

void CMesh::UpdateData()
{
	UINT	elementSize = sizeof(Vtx);
	UINT	iOffset = 0;

	CONTEXT->IASetVertexBuffers(0, 1, m_VB.GetAddressOf(), &elementSize, &iOffset);
	CONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void CMesh::Render()
{
	CONTEXT->DrawIndexed(m_iIdxCnt, 0, 0);
}
