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
	float m_fFOV;			// �þ߰� (Filed Of View)
	
	// �������� Orthographic
	float m_fWidth;			// �������� ���� ����
	float m_fScale;			// �������� ����

	// ����
	Vec2	m_v2Resolution;	// �ػ�
	float	m_fAspectRatio;	// ��Ⱦ��
	float	m_fNear;		// ���� �ּ� �Ÿ�
	float	m_fFar;			// ���� �ִ� �Ÿ�

	Matrix m_matView;		// View ��ȯ ���
	Matrix m_matProj;		// Projection ��ȯ ���
	
private:
	void ViewMatrix();			// View ��ȯ ��� ���
	void ProjectionMatrix();	// Projection ��ȯ ��� ���

public:
	virtual void Begin() override {};
	virtual void Tick() override {};
	virtual void FinalTick() override;
	virtual void UpdateData() override {};


};

