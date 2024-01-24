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
	Vec2	m_v2Dir;

public:
	void SetDir(Vec2 _dir) { m_v2Dir = _dir; }

public:
	virtual void Begin() override {}
	virtual void Tick() override;
	virtual void FinalTick() override {}
	virtual void UpdateData() override {}
};

