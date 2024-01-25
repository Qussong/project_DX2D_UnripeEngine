#pragma once

class CMesh
	: public CAsset
{
	using Super = CAsset;

public:
	CMesh();
	virtual ~CMesh();

private:
	ComPtr<ID3D11Buffer>	m_VB;			// VertexBuffer
	ComPtr<ID3D11Buffer>	m_IB;			// IndexBuffer

	uint32					m_iVtxCnt;
	uint32					m_iIdxCnt;

	void*					m_pVtxSysMem;
	void*					m_pIdxSysMem;


public:
	void Create(void* _vtx, uint32 _vtxCnt, void* _idx, uint32 _idxCnt);
	virtual void UpdateData() override;
	void Render();
};

