#pragma once

class CLight2D
	: public CComponent
{
	using Super = CComponent;

public:
	CLight2D();
	virtual ~CLight2D();

private:
	tLightInfo	m_tLightInfo;	// ±¤¿ø¿¡ ´ëÇÑ Á¤º¸

public:
	// Getter
	const tLightInfo& GetLightInfo() { return m_tLightInfo; }
	Vec4 GetLightColor() { return m_tLightInfo.v4Color; }
	Vec4 GetSpecular() { return m_tLightInfo.v4Specular; }	// ¹Ý»ç±¤
	Vec4 GetAmbient() { return m_tLightInfo.v4Ambient; }	// È¯°æ±¤(ÁÖº¯±¤)
	LIGHT_TYPE GetLightType() { return (LIGHT_TYPE)m_tLightInfo.iLightType; }
	float GetRadius() { return m_tLightInfo.fRadius; }
	float GetAngle() { return m_tLightInfo.fAngle; }

	// Setter
	void SetLightColor(Vec4 _color) { m_tLightInfo.v4Color = _color; }
	void SetSpecular(Vec4 _specular) { m_tLightInfo.v4Specular = _specular; }
	void SetAmbient(Vec4 _ambient) { m_tLightInfo.v4Ambient = _ambient; }
	void SetLightType(LIGHT_TYPE _type) { m_tLightInfo.iLightType = (uint32)_type; }
	void SetRaius(float _radius) { m_tLightInfo.fRadius = _radius; }
	void SetAngle(float _angle) { m_tLightInfo.fAngle = _angle; }

public:
	virtual void Begin() override {};
	virtual void Tick() override {};
	virtual void FinalTick() override;
	virtual void UpdateData() override {};
};

