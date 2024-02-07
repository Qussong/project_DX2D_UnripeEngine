#pragma once

class CCameraScript
	: public CScript
{
public:
	CCameraScript();
	virtual ~CCameraScript();

private:
	float	m_fCamSpeed;
	float	m_fDragSpeed;
	float	m_fWheelSpeed;

private:
	virtual void Tick() override;
};

