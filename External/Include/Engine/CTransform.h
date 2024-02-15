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
	// local
	Vec3	m_v3LocalPostion;					// localS
	Vec3	m_v3LocalScale;						// localR
	Vec3	m_v3LocalRotation;					// localT
	Vec3	m_arrLocalDir[(UINT)DIR_TYPE::END];	// localDir
	Matrix	m_matLocal;							// localMatrix

	// world
	Vec3	m_arrWorldDir[(UINT)DIR_TYPE::END];	// WorldDir
	Matrix	m_matWorld;							// WorldMatrix
	bool	m_bAbsolute;						// 부모객체로부터 Scale 영향(기본 값 : false = 받음)

public:
	virtual void Begin() override {};
	virtual void Tick() override {};
	virtual void FinalTick() override;
	virtual void UpdateData() override;

private:
	Vec3 WorldSRT(SRT_TYPE _type);
	Vec3 ToEulerAngles(Quaternion q);

public:
	// Getter
	const Vec3		GetLocalScale() { return m_v3LocalScale; }
	const Vec3		GetLocalRotation() { return m_v3LocalRotation; }
	const Vec3		GetLocalPos() { return m_v3LocalPostion; }
	const Vec3		GetLocalDirection(DIR_TYPE _dir) { return m_arrLocalDir[(uint32)_dir]; }
	const Matrix	GetLocalMatrix() { return m_matLocal; }
	const Vec3		GetWorldScale();
	const Vec3		GetWorldRotation();
	const Vec3		GetWorldPos();
	const Vec3		GetWorldDirection(DIR_TYPE _dir) { return m_arrWorldDir[(uint32)_dir]; }
	const Matrix	GetWorldMatrix() { return m_matWorld; }
	const bool		IsAffectScale() { return m_bAbsolute; }

	// Setter
	void SetLocalPos(Vec3 _pos) { m_v3LocalPostion = _pos; }
	void SetLocalPos(Vec2 _pos);
	void SetLocalScale(Vec3 _scale) { m_v3LocalScale = _scale; }
	void SetLocalRotation(Vec3 _rotate) { m_v3LocalRotation = _rotate; }
	void SetWorldMatrix(Matrix _mat) { m_matWorld = _mat; }
	void SetAffectScale(bool _flag) { m_bAbsolute = _flag; }
};