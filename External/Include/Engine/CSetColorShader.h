#pragma once

//class CTexture;
//class CComputeShader;
#include "CComputeShader.h"

class CSetColorShader
	: public CComputeShader
{
	using Super = CComputeShader;

public:
	CSetColorShader();
	virtual ~CSetColorShader();

private:
	Ptr<CTexture>	m_pTargetTex;
	Vec4			m_v4Color;

public:
	void SetTargetTex(Ptr<CTexture> _tex) { m_pTargetTex = _tex; }
	void SetColor(Vec3 _color) { m_v4Color = Vec4(_color, 0.f); }

public:
	virtual void UpdateData() override;
	virtual void Clear() override;
};

