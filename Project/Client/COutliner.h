#pragma once

class COutliner
	: public CUI
{
	using Super = CUI;

public:
	COutliner();
	virtual ~COutliner();

private:


public:
	virtual void Tick() override;
	virtual void Render_Update() override;
};

