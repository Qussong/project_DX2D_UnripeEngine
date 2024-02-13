#pragma once

class COverlay
	: public CUI
{
	using Super = CUI;

public:
	COverlay();
	virtual ~COverlay();

public:
	virtual void SetWindowOption() override;
	virtual void Render_Update() override;
};

