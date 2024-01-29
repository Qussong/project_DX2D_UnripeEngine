#pragma once

class CMaterial
	: public CAsset
{
	using Super = CAsset;

public:
	CMaterial();
	virtual ~CMaterial();

public:
	tMaterial				m_tConst;
	Ptr<CTexture>			m_arrTex[(UINT)TEX_PARAM::END];
	Ptr<CGraphicShader>		m_pShader;

public:
	virtual void UpdateData() override;
	virtual int Load(const wstring& _strFilePath) override { return E_FAIL; };

public:
	void SetShader(Ptr<CGraphicShader> _shader) { m_pShader = _shader; }
	Ptr<CGraphicShader> GetShader() { return m_pShader; }

	//template<typename T>
	//void SetScalarParam(SCALAR_PARAM _ParamType, const T& _Value);
	//void SetTexParam(TEX_PARAM _Param, Ptr<CTexture> _pTex);
};

