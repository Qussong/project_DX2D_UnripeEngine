#pragma once

class CCamera
	:public CComponent
{
	using Super = CComponent;

public:
	CCamera();
	virtual ~CCamera();

private:
	// 원근투영 Perspective
	float m_fFOV;
	
	// 직교투영 Orthographic
	float m_fWidth;
	float m_fHeight;

	// 공용
	float m_fAspectRatio;
	float m_fFar;

	Matrix m_matView;	// View 변환 행렬
	Matrix m_matProj;	// Projection 변환 행렬
	
public:
	virtual void Begin() override {};
	virtual void Tick() override {};
	virtual void FinalTick() override;
	virtual void UpdateData() override {};
};

