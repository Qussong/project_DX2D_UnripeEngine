#pragma once

class CCamera
	:public CComponent
{
	using Super = CComponent;

public:
	CCamera();
	virtual ~CCamera();

private:
	PROJ_TYPE	m_eProjType;	// 투영타입

	// 원근투영 Perspective
	float		m_fFOV;			// 시야각 (Filed Of View)
	
	// 직교투영 Orthographic
	float		m_fScale;		// 직교투영 배율

	// 공용
	Vec2		m_v2Resolution;	// 해상도
	float		m_fAspectRatio;	// 종횡비
	float		m_fNear;		// 투영 최소 거리
	float		m_fFar;			// 투영 최대 거리

	Matrix		m_matView;		// View 변환 행렬
	Matrix		m_matProj;		// Projection 변환 행렬
	
private:
	void ViewMatrix();			// View 변환 행렬 계산
	void ProjectionMatrix();	// Projection 변환 행렬 계산

public:
	PROJ_TYPE GetProjectionType() { return m_eProjType; }
	void SetProjectionType(PROJ_TYPE _type) { m_eProjType = _type; }

public:
	virtual void Begin() override {};
	virtual void Tick() override {};
	virtual void FinalTick() override;
	virtual void UpdateData() override {};


};

