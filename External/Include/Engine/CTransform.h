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

	// world
	Vec3	m_arrWorldDir[(UINT)DIR_TYPE::END];	// WorldDir
	Matrix	m_matWorld;							// WorldMatrix

	bool	m_isAffectScale;					// 부모객체로부터 Scale 영향(true = 받음, false = 안받음)

public:
	virtual void Begin() override {};
	virtual void Tick() override {};
	virtual void FinalTick() override;
	virtual void UpdateData() override;

public:
	// local
	void SetLocalPos(Vec3 _pos) { m_v3LocalPostion = _pos; }
	void SetLocalScale(Vec3 _scale) { m_v3LocalScale = _scale; }
	void SetLocalRotation(Vec3 _rotate) { m_v3LocalRotation = _rotate; }
	
	// world
	void SetWorldMatrix(Matrix _mat) { m_matWorld = _mat; }

	// local
	Vec3 GetLocalPos() { return m_v3LocalPostion; }
	Vec3 GetLocalScale() { return m_v3LocalScale; }
	Vec3 GetLocalRotation() { return m_v3LocalRotation; }
	Vec3 GetLocalDirection(DIR_TYPE _dir) { return m_arrLocalDir[(uint32)_dir]; }

	// world
	Vec3 GetWorldDirection(DIR_TYPE _dir) { return m_arrWorldDir[(uint32)_dir]; }
	Matrix GetWorldMatrix() { return m_matWorld; }

	void SetAffectScale(bool _flag) { m_isAffectScale = _flag; }
};