#pragma once
class CContent
	: public CUI
{
	using Super = CUI;

public:
	CContent();
	virtual ~CContent();

private:

public:
	virtual void Tick() override;
	virtual void Render_Update() override;
};

