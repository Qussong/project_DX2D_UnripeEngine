#pragma once

class CMaterial
	: public CAsset
{
	using Super = CAsset;

public:
	CMaterial();
	virtual ~CMaterial();

public:
	tMaterial			m_tConst;
	CTexture*			m_arrTex[(UINT)TEX_PARAM::END];
	CGraphicShader*		m_pShader;

public:
	virtual void UpdateData() override;

public:

	void SetShader(CGraphicShader* _shader) { m_pShader = _shader; }
	CGraphicShader* GetShader() { return m_pShader; }
};

