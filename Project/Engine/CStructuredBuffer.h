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
	UINT								m_iElementSize;
	UINT								m_iElementCnt;
	SB_TYPE								m_eType;

public:
	int32 Create(UINT _elementSize,
				 UINT _elementCnt,
				 SB_TYPE _type = SB_TYPE::READ_ONLY,
				 void* _sysMem = nullptr);
	void UpdateData(UINT _registerNum);
	
};

