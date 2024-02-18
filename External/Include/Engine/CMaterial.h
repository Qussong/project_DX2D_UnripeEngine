#pragma once

class CMaterial
	: public CAsset
{
	using Super = CAsset;

public:
	CMaterial();
	virtual ~CMaterial();

public:
	tMaterial				m_tMtrlConst;
	Ptr<CTexture>			m_arrTex[(UINT)TEX_PARAM::END];	// TEX_PARAM::TEX_0 ~ TEX_5
	Ptr<CGraphicShader>		m_pShader;

public:
	virtual void UpdateData();

public:
	void SetShader(Ptr<CGraphicShader> _shader) { m_pShader = _shader; }
	Ptr<CGraphicShader> GetShader() { return m_pShader; }

	template<typename T>
	void SetScalarParam(SCALAR_PARAM _eParamType, const T& _value);	// 원하는 곳에 Scalar 값 세팅
	void SetTexParam(TEX_PARAM _eParam, Ptr<CTexture> _pTex);		// 원하는 곳에 Texture 세팅
};

template<typename T>
inline void CMaterial::SetScalarParam(SCALAR_PARAM _eParamType, const T& _value)
{
	const T* pValue = &_value;

	switch (_eParamType)
	{
	case SCALAR_PARAM::INT_0:
	case SCALAR_PARAM::INT_1:
	case SCALAR_PARAM::INT_2:
	case SCALAR_PARAM::INT_3:
	{
		m_tMtrlConst.iArr[(int32)_eParamType] = *((int*)pValue);
	}
	break;
	case SCALAR_PARAM::FLOAT_0:
	case SCALAR_PARAM::FLOAT_1:
	case SCALAR_PARAM::FLOAT_2:
	case SCALAR_PARAM::FLOAT_3:
	{
		int32 eFLOAT_0 = (int32)SCALAR_PARAM::FLOAT_0;
		m_tMtrlConst.fArr[(int32)_eParamType - eFLOAT_0] = *((float*)pValue);
	}
	break;
	case SCALAR_PARAM::VEC2_0:
	case SCALAR_PARAM::VEC2_1:
	case SCALAR_PARAM::VEC2_2:
	case SCALAR_PARAM::VEC2_3:
	{
		int32 VEC2_0 = (int32)SCALAR_PARAM::VEC2_0;
		m_tMtrlConst.v2Arr[(int32)_eParamType - VEC2_0] = *((Vec2*)pValue);
	}
	break;
	case SCALAR_PARAM::VEC4_0:
	case SCALAR_PARAM::VEC4_1:
	case SCALAR_PARAM::VEC4_2:
	case SCALAR_PARAM::VEC4_3:
	{
		int32 VEC4_0 = (int32)SCALAR_PARAM::VEC4_0;
		m_tMtrlConst.v4Arr[(int32)_eParamType - VEC4_0] = *((Vec4*)pValue);
	}
	break;
	case SCALAR_PARAM::MAT_0:
	case SCALAR_PARAM::MAT_1:
	case SCALAR_PARAM::MAT_2:
	case SCALAR_PARAM::MAT_3:
	{
		int32 MAT_0 = (int32)SCALAR_PARAM::MAT_0;
		m_tMtrlConst.matArr[(int32)_eParamType - MAT_0] = *((Matrix*)pValue);
	}
	break;
	}
}
