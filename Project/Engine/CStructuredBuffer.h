#pragma once

class CStructuredBuffer
	: public CEntity
{
public:
	CStructuredBuffer();
	virtual ~CStructuredBuffer();

private:
	ComPtr<ID3D11Buffer>				m_SB;
	ComPtr<ID3D11ShaderResourceView>	m_SRV;

	ComPtr<ID3D11Buffer>				m_SB_Read;		// GPU -> SysMem
	ComPtr<ID3D11Buffer>				m_SB_Write;		// SysMem -> GPU

	UINT								m_iElementSize;
	UINT								m_iElementCnt;
	SB_TYPE								m_eType;
	bool								m_bSysMemMove;	// ?

public:
	// Getter
	UINT GetElementSize() { return m_iElementSize; }
	UINT GetElementCnt() { return m_iElementCnt; }
	UINT GetBufferSize() { return m_iElementSize * m_iElementCnt; }

	// Setter
	void SetData(void* _src, UINT _elementCnt = 0);
	void GetData(void* _dest, UINT _elementCnt);

public:
	int32 Create(UINT _elementSize,
				 UINT _elementCnt,
				 SB_TYPE _type = SB_TYPE::READ_ONLY,
				 bool _sysMemMove = false,
				 void* _sysMem = nullptr);
	void UpdateData(UINT _registerNum);
};

