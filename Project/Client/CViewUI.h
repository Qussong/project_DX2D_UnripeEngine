#pragma once
class CViewUI
	: public CUI
{
	using Super = CUI;

public:
	CViewUI();
	virtual ~CViewUI();

public:
	virtual void SetWindowOption() override;
	virtual void Render_Update() override;
};