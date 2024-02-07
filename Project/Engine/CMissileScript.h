#pragma once

class CMissileScript
	: public CScript
{
	using Super = CScript;

public:
	CMissileScript();
	virtual ~CMissileScript();

private:
	float	m_fSpeed;

public:
	virtual void Tick() override;
};

