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
	virtual void Begin() override {}
	virtual void Tick() override;
	virtual void FinalTick() override {}
	virtual void UpdateData() override {}
};

