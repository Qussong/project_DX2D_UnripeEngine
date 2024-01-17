#pragma once

class CCamera
	:public CComponent
{
	using Super = CComponent;

public:
	CCamera();
	virtual ~CCamera();

private:
	// �������� Perspective
	float m_fFOV;
	
	// �������� Orthographic
	float m_fWidth;
	float m_fHeight;

	// ����
	float m_fAspectRatio;
	float m_fFar;

	Matrix m_matView;	// View ��ȯ ���
	Matrix m_matProj;	// Projection ��ȯ ���
	
public:
	virtual void Begin() override {};
	virtual void Tick() override {};
	virtual void FinalTick() override;
	virtual void UpdateData() override {};
};

