#pragma once

class CMinimapScript
	: public CScript
{
	using Super = CScript;

public:
	CMinimapScript();
	virtual ~CMinimapScript();

public:
	virtual void Tick() override;
};

