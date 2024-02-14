#pragma once

class CMeshRenderUI
	: public CComponentUI
{
	using Super = CComponentUI;

public:
	CMeshRenderUI();
	virtual ~CMeshRenderUI();


public:
	virtual void Tick() override {}
	virtual void SetWindowOption() override {}	// UI芒 可记 技泼
	virtual void Render_Update() override;		// UI芒 备己 技泼
};

