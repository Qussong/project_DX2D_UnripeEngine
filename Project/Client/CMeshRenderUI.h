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
	virtual void SetWindowOption() override {}	// UIâ �ɼ� ����
	virtual void Render_Update() override;		// UIâ ���� ����
};

