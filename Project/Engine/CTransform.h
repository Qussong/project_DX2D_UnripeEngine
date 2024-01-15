#pragma once
#include "CComponent.h"

class CTransform
	: public CComponent
{
	using Super = CComponent;

public:
	CTransform();
	virtual ~CTransform();

private:
	Vec3	m_v3RelativePostion;
	Vec3	m_v3RelativeScale;
	Vec3	m_v3RelativeRotation;
	Vec3	m_arrDirection[3];
	Matrix	m_matWorld;

public:
	virtual void Begin() override;
	virtual void Tick() override;
	virtual void FinalTick() override;
	virtual void UpdateData() override;

public:
	void SetRelativePos(Vec3 _pos) { m_v3RelativePostion = _pos; }
	void SetRelativeScale(Vec3 _scale) { m_v3RelativeScale = _scale; }
	void SetRelativeRotation(Vec3 _rotate) { m_v3RelativeRotation = _rotate; }
	void SetWorldMatrix(Matrix _mat) { m_matWorld = _mat; }

	Vec3 GetRelativePos() { return m_v3RelativePostion; }
	Vec3 GetRelativeScale() { return m_v3RelativeScale; }
	Vec3 GetRelativeRotation() { return m_v3RelativeRotation; }
	Matrix GetWorldMatrix() { return m_matWorld; }
	Vec3 GetDirection(DIR_TYPE _dir) { return m_arrDirection[(uint32)_dir]; }
};

